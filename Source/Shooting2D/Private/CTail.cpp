#include "CTail.h"
#include <Components/StaticMeshComponent.h>
//#include "CSpaceship.h"
//#include "Kismet/GameplayStatics.h"

ACTail::ACTail()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"StaticMesh");
	SetRootComponent(StaticMesh);
}

void ACTail::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어를 가져오는 방법
	if (AActor* target = GetWorld()->GetFirstPlayerController()->GetPawn())
		Target = target;
	
	//if (AActor* target = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	//	Target = target;

	//if (AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), ACSpaceship::StaticClass()))
	//	Target = target;
}

void ACTail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Target을 따라 이동
	// P = P0 + vt;
	if (!!Target)
	{
		FVector P0 = this->GetActorLocation();
		FVector direction = (Target->GetActorLocation() - P0);
		FVector v = direction.GetSafeNormal() * Speed;

		SetActorLocation(P0 + v * DeltaTime);

		float distance = Target->GetDistanceTo(this);
		//float distance = FVector::Dist(Target->GetActorLocation(), this->GetActorLocation());
		//float distance = direction.Size();

	}
}
