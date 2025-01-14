#include "CEnemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CSpaceship.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ������Ʈ ����
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
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

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	this->Destroy();
}
