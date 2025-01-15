#include "CDestroyZone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CSpaceship.h"

ACDestroyZone::ACDestroyZone()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	// �ڽ��� ũ�⸦ FVector(50, 50, 50)���� ����
	Box->SetBoxExtent(FVector(50));
	SetRootComponent(Box);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	// �ڽ� ������Ʈ�� �����Ƽ�� ���� ���·� ����
	Box->SetMobility(EComponentMobility::Static);

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// �ݸ��� ������ DestroyZone ����
	Box->SetCollisionProfileName(L"DestroyZone");

	//// ��������Ʈ�� ����Ͽ� �ش��Լ��� ����
	//Box->OnComponentBeginOverlap.AddDynamic(this, &ACDestroyZone::OnComponentBeginOverlap);
}

void ACDestroyZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDestroyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDestroyZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA<ACSpaceship>())
		return;

	OtherActor->Destroy();
}

//void ACDestroyZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (ACSpaceship* space = Cast<ACSpaceship>(OtherActor))
//		return;
//
//	OtherActor->Destroy();
//}
