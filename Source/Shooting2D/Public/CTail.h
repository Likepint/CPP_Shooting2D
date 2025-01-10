#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTail.generated.h"

// Tail -> 플레이어를 따라 이동
// Target, Speed

UCLASS()
class SHOOTING2D_API ACTail : public AActor
{
	GENERATED_BODY()

public:
	// Static Mesh
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
public:	
	ACTail();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// Target
	UPROPERTY(EditInstanceOnly)
	class AActor* Target;

	// Speed
	UPROPERTY(EditInstanceOnly)
	float Speed = 450;
};
