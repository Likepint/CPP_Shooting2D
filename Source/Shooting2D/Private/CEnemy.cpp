#include "CEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 컴포넌트 생성
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	// 스태틱 메시 컴포넌트 생성
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Box);
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
			Direction = target->GetActorLocation() - this->GetActorLocation();
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

