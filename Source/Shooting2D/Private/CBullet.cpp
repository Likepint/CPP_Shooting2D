#include "CBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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
