#include "CSpaceship.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

ACSpaceship::ACSpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 컴포넌트를 Root 컴포넌트로 설정
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	// Box Extent 50
	Box->SetBoxExtent(FVector(50, 50, 50));

	// 스태틱 메시 컴포넌트를 Root 컴포넌트에 Attach
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Box);

	// 스태틱 메시 기본 큐브 설정
	ConstructorHelpers::FObjectFinder<UStaticMesh> cube(L"/Script/Engine.StaticMesh'/Game/PJS/Meshes/Cube.Cube'");
	if (!!cube.Succeeded())
		StaticMesh->SetStaticMesh(cube.Object);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(0, 0, 100));
	Arrow->SetRelativeRotation(FQuat(FRotator(90, 0, 0)));

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// 콜리전 프리셋 Custom 설정
	Box->SetCollisionProfileName(L"Custom");
	// 충돌 응답 Query And Physics로 설정
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Object Type을 1번 채널(Player)로 설정
	Box->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	// 전체 채널 무시 설정
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// 에너미 채널 오버랩 설정
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
	// DestroyZone과 오버랩 설정
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	//// 델리게이트를 사용하여 해당함수를 연결
	//Box->OnComponentBeginOverlap.AddDynamic(this, &ACSpaceship::OnComponentBeginOverlap);
}

void ACSpaceship::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ACGameMode>(GetWorld()->GetAuthGameMode());
	// GameOverUI 숨김처리, 마우스 커서 초기화, 게임 일시정지 해제, 게임화면으로 포커스 설정 등 초기화 설정
	GM->ShowGameOver(false);

	//// 게임 일시 정지 해제
	//UGameplayStatics::SetGamePaused(GetWorld(), false);

	//// 마우스 커서
	//APlayerController* controller = GetWorld()->GetFirstPlayerController();
	//controller->SetShowMouseCursor(false);

	//// 포커스를 게임화면에 고정
	//controller->SetInputMode(FInputModeGameOnly());

	// 현재 체력을 최대 체력으로 설정
	CurHP = MaxHP;

	// HP ProgressBar 갱신
	GM->SetHP(CurHP, MaxHP);

	// Magazine Pool 총알 20개 추가
	for (int32 i = 0; i < 20; ++i)
	{
		FActorSpawnParameters params;
		// 항상 스폰
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(BulletFactory, params);
		bullet->SetActive(false);

		Magazine.Add(bullet);
	}

	//// Hello World / LOG
	//UE_LOG(LogTemp, Warning, L"Hello World");

	//// Debug Message
	//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, L"Hello World");

	//UE_LOG(LogTemp, Warning, TEXT("%d"), Num);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), bGood);

	//// 문자열
	//// FString : 문자열을 조합해서 생성, 주로 사용하는 문자열 자료형
	//// FText, FName
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *MyName);

}

void ACSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//{   // 오른쪽으로 이동
	//    // P = P0 + v(direction * speed) * t
	//	FVector p0 = GetActorLocation();
	//	FVector v = GetActorRightVector() * Speed;

	//	SetActorLocation(p0 + v * DeltaTime);
	//}

	{ // 사용자의 입력에 따라 상하좌우 이동
		// 상하좌우방향
		FVector dir = FVector(0, Horizontal, Vertical);

		// 길이가 1인 방향 벡터
		dir.Normalize();

		// P = P0 + vt
		FVector p0 = GetActorLocation();
		FVector v = dir * Speed;

		SetActorLocation(p0 + v * DeltaTime, true);
		//SetActorLocation(GetActorLocation() + dir.GetSafeNormal() * Speed, DeltaTime);
	}

	{// 자동 발사
		if (bAutoFire) // bAutoFire == true
		{
			// 시간 누적
			CurrentTime += DeltaTime;

			// 누적 시간이 발사 시간이 되면
			if (CurrentTime >= FireTime)
			{
				// 총알 생성
				MakeBullet();

				// 누적 시간 초기화
				CurrentTime = 0;
			}
		}
	}
}

void ACSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(L"Vertical", this, &ACSpaceship::OnAxisVertical);
	PlayerInputComponent->BindAxis(L"Horizontal", this, &ACSpaceship::OnAxisHorizontal);

	//PlayerInputComponent->BindAction(L"Fire", EInputEvent::IE_Pressed, this, &ACSpaceship::OnFire);

	PlayerInputComponent->BindAction(L"AutoFire", EInputEvent::IE_Pressed, this, &ACSpaceship::OnAutoFireClick);

	PlayerInputComponent->BindAction(L"Fire", EInputEvent::IE_Pressed, this, &ACSpaceship::OnAutoFirePressed);
	PlayerInputComponent->BindAction(L"Fire", EInputEvent::IE_Released, this, &ACSpaceship::OnAutoFirePressed);
}

void ACSpaceship::MakeBullet()
{
	bool bFindResult = false;

	FTransform transform = Arrow->GetComponentTransform();

	// 탄창을 전부 검사해서 비활성화된 총알을 탐색
	for (auto& bullet : Magazine)
	{
		// 찾았다면 그 총알을 활성화 후 총구 위치에 배치
		if (!bullet->StaticMesh->GetVisibleFlag()) // == false
		{
			bFindResult = !bFindResult;

			// 활성화 시키고 총구 위치에 배치
			bullet->SetActive(true);
			bullet->SetActorTransform(transform);

			// 소리 재생
			UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
			
			// 반복 탈출
			break;
		}
	}

	if (!bFindResult) {} // == false
		// 추가로 총알 생성
}

void ACSpaceship::OnAxisVertical(float InVal)
{
	Vertical = InVal;

	//FVector P0 = GetActorLocation();
	//FVector direction = (GetActorUpVector() * InVal).GetSafeNormal();
	//FVector v = direction * Speed;

	//SetActorLocation(P0 + v * GetWorld()->GetDeltaSeconds());
}

void ACSpaceship::OnAxisHorizontal(float InVal)
{
	Horizontal = InVal;

	//FVector P0 = GetActorLocation();
	//FVector direction = (GetActorRightVector() * InVal).GetSafeNormal();
	//FVector v = direction * Speed;

	//SetActorLocation(P0 + v * GetWorld()->GetDeltaSeconds());
}

void ACSpaceship::OnFire()
{
	MakeBullet();

	//FTransform transform = Arrow->GetComponentTransform();

	//GetWorld()->SpawnActor(BulletFactory, &transform);

	//if (!!FireSound)
	//	UGameplayStatics::PlaySound2D(GetWorld(), FireSound);
}

void ACSpaceship::OnAutoFireClick()
{
	bAutoFire = !bAutoFire;

	CurrentTime = FireTime;
}

void ACSpaceship::OnAutoFirePressed()
{
	// 마우스 왼쪽 버튼을 누르면 bAutoFire를 On/Off 전환
	bAutoFire = !bAutoFire;

	// bAutoFire가 활성화되면, 총알 한발 발사
	if (bAutoFire)
		CurrentTime = FireTime;
}

void ACSpaceship::OnDamaged(int32 InDamage)
{
	CurHP -= InDamage;
	
	// HP Bar 갱신
	GM->SetHP(CurHP, MaxHP);
}

//void ACSpaceship::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (ACEnemy* enemy = Cast<ACEnemy>(OtherActor))
//	{
//		OnDamaged(1);
//		//APlayerController* controller = Cast<APlayerController>(GetController());
//
//		//UKismetSystemLibrary::QuitGame(GetWorld(), controller, EQuitPreference::Quit, true);
//	}
//}

//int32 ACSpaceship::MyAddCallable(int32 a, int32 b)
//{
//
//	return a + b;
//}
//
//int32 ACSpaceship::MyAddPure(int32 a, int32 b)
//{
//
//	return a + b;
//}
//
//int32 ACSpaceship::MyAddNativeEvent_Implementation(int32 a, int32 b)
//{
//	return a + b;
//}
