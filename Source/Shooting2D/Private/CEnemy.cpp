#include "CEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CSpaceship.h"
#include "Kismet/KismetMathLibrary.h"
#include "CGameMode.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ������Ʈ ����
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetBoxExtent(FVector(50));
	SetRootComponent(Box);

	// ����ƽ �޽� ������Ʈ ����
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Box);

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// �ݸ��� ������ Custom ����
	Box->SetCollisionProfileName(L"Enemy");

	// ��������Ʈ�� ����Ͽ� �ش��Լ��� ����
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// 30�ۼ�Ʈ�� Ȯ���� �÷��̾� �������� �̵�
	int32 rate = FMath::RandRange(1, 100);

	if (rate <= RateTo)
	{
		// �÷��̾ Ÿ������ ����
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

			// ���� ���Ӹ�� �ε�
			ACGameMode* GM = Cast<ACGameMode>(GetWorld()->GetAuthGameMode());

			if (!!GM)
				GM->ShowGameOver(true);
		}
	}

	this->Destroy();
}
