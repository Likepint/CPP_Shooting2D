#include "CEnemyFactory.h"
#include "CEnemy.h"
#include "Components/ArrowComponent.h"

ACEnemyFactory::ACEnemyFactory()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(L"Root");
	SetRootComponent(Root);

	Arrow = CreateDefaultSubobject<UArrowComponent>(L"Arrow");
	Arrow->SetupAttachment(Root);
	// (Pitch=-90.000000,Yaw=180.000000,Roll=0.000000)
	Arrow->SetRelativeRotation(FRotator(-90, 180, 0));
}

void ACEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	// Set Timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACEnemyFactory::SpawnEnemy, SpawnTime, true);
}

void ACEnemyFactory::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Clear Timer
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ACEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DelayTime += DeltaTime; // 딜레이타임 측정

	//if (DelayTime > SpawnTime) // 딜레이타임이 생성시간을 초과하면
	//{
	//	if (!!Enemy)
	//	{
	//		SpawnEnemy();

	//		DelayTime = 0; // 딜레이 타임 초기화
	//	}
	//}
}

void ACEnemyFactory::SpawnEnemy()
{
	FActorSpawnParameters params;

	FTransform transform = Root->GetComponentTransform();
	float y = FMath::FRandRange(-1000.f, 1000.f);

	transform.SetLocation
	(
		FVector
		(
			transform.GetLocation().X,
			y,
			transform.GetLocation().Z
		)
	);

	GetWorld()->SpawnActor(Enemy, &transform, params); // 적 생성
}
