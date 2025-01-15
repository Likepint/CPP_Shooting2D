#include "CBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CEnemy.h"
#include "CGameMode.h"

ACBullet::ACBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	Box->SetBoxExtent(FVector(50));
	Box->SetRelativeScale3D(FVector(1, 0.25, 1));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	// 생성자 도우미를 이용하여 에셋 로드
	ConstructorHelpers::FObjectFinder<UStaticMesh> asset(L"/Script/Engine.StaticMesh'/Game/PJS/Meshes/Cube.Cube'");
	if (asset.Succeeded())
		StaticMesh->SetStaticMesh(asset.Object);

	// Overlap Event
	Box->SetGenerateOverlapEvents(true);
	// 콜리전 프리셋 Custom 설정
	Box->SetCollisionProfileName(L"Bullet");

	// 델리게이트를 사용하여 해당함수를 연결
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACBullet::OnComponentBeginOverlap);
}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();

}

void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p0 = GetActorLocation();
	FVector v = GetActorForwardVector() * Speed;
	
	SetActorLocation(p0 + v * DeltaTime);
}

void ACBullet::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACEnemy* enemy = Cast<ACEnemy>(OtherActor))
	{
		enemy->Destroy();

		// 현재 게임모드 로드 후 AddScore() 함수를 호출하여 점수 누적
		if (ACGameMode* mode = Cast<ACGameMode>(GetWorld()->GetAuthGameMode()))
			mode->AddScore(1);
	}

	this->Destroy();
}
