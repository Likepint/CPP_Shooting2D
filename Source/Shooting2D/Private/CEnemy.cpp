#include "CEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CSpaceship.h"
#include "Kismet/KismetMathLibrary.h"
#include "CGameMode.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 컴포넌트 생성
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetBoxExtent(FVector(50));
	SetRootComponent(Box);

	// 스태틱 메시 컴포넌트 생성
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Box);

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// 콜리전 프리셋 Custom 설정
	Box->SetCollisionProfileName(L"Enemy");

	// 델리게이트를 사용하여 해당함수를 연결
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// 30퍼센트의 확률로 플레이어 방향으로 이동
	int32 rate = FMath::RandRange(1, 100);

	if (rate <= RateTo)
	{
		// 플레이어를 타겟으로 설정
		if (APawn* target = GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			Direction = target->GetActorLocation() - this->GetActorLocation();

			FRotator rotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), target->GetActorLocation());

			this->SetActorRotation(FQuat(rotator));
		}
	}
	else Direction = GetActorUpVector() * -1;
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = p0 + vt;
	FVector p0 = GetActorLocation();
	FVector v = Direction.GetSafeNormal() * Speed;

	SetActorLocation(p0 + v * DeltaTime);
}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACSpaceship* space = Cast<ACSpaceship>(OtherActor))
	{
		space->OnDamaged(1);

		if (space->GetCurHP() <= 0)
		{
			space->Destroy();

			// 현재 게임모드 로드
			ACGameMode* GM = Cast<ACGameMode>(GetWorld()->GetAuthGameMode());

			if (!!GM)
				GM->ShowGameOver(true);
		}
	}

	this->Destroy();
}
