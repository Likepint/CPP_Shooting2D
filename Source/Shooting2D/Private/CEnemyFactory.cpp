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

	//DelayTime += DeltaTime; // ������Ÿ�� ����

	//if (DelayTime > SpawnTime) // ������Ÿ���� �����ð��� �ʰ��ϸ�
	//{
	//	if (!!Enemy)
	//	{
	//		SpawnEnemy();

	//		DelayTime = 0; // ������ Ÿ�� �ʱ�ȭ
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

	GetWorld()->SpawnActor(Enemy, &transform, params); // �� ����
}
