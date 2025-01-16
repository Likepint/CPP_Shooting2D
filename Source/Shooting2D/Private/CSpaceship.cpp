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

	// �浹ü ������Ʈ�� Root ������Ʈ�� ����
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	// Box Extent 50
	Box->SetBoxExtent(FVector(50, 50, 50));

	// ����ƽ �޽� ������Ʈ�� Root ������Ʈ�� Attach
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Box);

	// ����ƽ �޽� �⺻ ť�� ����
	ConstructorHelpers::FObjectFinder<UStaticMesh> cube(L"/Script/Engine.StaticMesh'/Game/PJS/Meshes/Cube.Cube'");
	if (!!cube.Succeeded())
		StaticMesh->SetStaticMesh(cube.Object);

	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(0, 0, 100));
	Arrow->SetRelativeRotation(FQuat(FRotator(90, 0, 0)));

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// �ݸ��� ������ Custom ����
	Box->SetCollisionProfileName(L"Custom");
	// �浹 ���� Query And Physics�� ����
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Object Type�� 1�� ä��(Player)�� ����
	Box->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	// ��ü ä�� ���� ����
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ���ʹ� ä�� ������ ����
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
	// DestroyZone�� ������ ����
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	//// ��������Ʈ�� ����Ͽ� �ش��Լ��� ����
	//Box->OnComponentBeginOverlap.AddDynamic(this, &ACSpaceship::OnComponentBeginOverlap);
}

void ACSpaceship::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ACGameMode>(GetWorld()->GetAuthGameMode());

	// ���� ü���� �ִ� ü������ ����
	CurHP = MaxHP;

	// HP ProgressBar ����
	GM->SetHP(CurHP, MaxHP);

	//// Hello World / LOG
	//UE_LOG(LogTemp, Warning, L"Hello World");

	//// Debug Message
	//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, L"Hello World");

	//UE_LOG(LogTemp, Warning, TEXT("%d"), Num);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), bGood);

	//// ���ڿ�
	//// FString : ���ڿ��� �����ؼ� ����, �ַ� ����ϴ� ���ڿ� �ڷ���
	//// FText, FName
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *MyName);

}

void ACSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//{   // ���������� �̵�
	//    // P = P0 + v(direction * speed) * t
	//	FVector p0 = GetActorLocation();
	//	FVector v = GetActorRightVector() * Speed;

	//	SetActorLocation(p0 + v * DeltaTime);
	//}

	{ // ������� �Է¿� ���� �����¿� �̵�
		// �����¿����
		FVector dir = FVector(0, Horizontal, Vertical);

		// ���̰� 1�� ���� ����
		dir.Normalize();

		// P = P0 + vt
		FVector p0 = GetActorLocation();
		FVector v = dir * Speed;

		SetActorLocation(p0 + v * DeltaTime, true);
		//SetActorLocation(GetActorLocation() + dir.GetSafeNormal() * Speed, DeltaTime);
	}
}

void ACSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(L"Vertical", this, &ACSpaceship::OnAxisVertical);
	PlayerInputComponent->BindAxis(L"Horizontal", this, &ACSpaceship::OnAxisHorizontal);

	PlayerInputComponent->BindAction(L"Fire", EInputEvent::IE_Pressed, this, &ACSpaceship::OnFire);
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
	FTransform transform = Arrow->GetComponentTransform();

	GetWorld()->SpawnActor(Bullet, &transform);
}

void ACSpaceship::OnDamaged(int32 InDamage)
{
	CurHP -= InDamage;
	
	// HP Bar ����
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
