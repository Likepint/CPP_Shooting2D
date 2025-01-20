#include "CDestroyZone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CSpaceship.h"
#include "CBullet.h"

ACDestroyZone::ACDestroyZone()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	// 박스의 크기를 FVector(50, 50, 50)으로 설정
	Box->SetBoxExtent(FVector(50));
	SetRootComponent(Box);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	// 박스 컴포넌트의 모빌리티를 고정 상태로 설정
	Box->SetMobility(EComponentMobility::Static);

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// 콜리전 프리셋 DestroyZone 설정
	Box->SetCollisionProfileName(L"DestroyZone");

	//// 델리게이트를 사용하여 해당함수를 연결
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
	// OtherActor == Bullet
	if (ACBullet* bullet = Cast<ACBullet>(OtherActor))
	{
		bullet->SetActive(false);

		return;
	}

	// OtherActor != CSpaceship
	if (!(OtherActor->IsA<ACSpaceship>()))
		OtherActor->Destroy();
}

//void ACDestroyZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (ACSpaceship* space = Cast<ACSpaceship>(OtherActor))
//		return;
//
//	OtherActor->Destroy();
//}
