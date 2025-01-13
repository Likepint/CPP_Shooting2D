#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

UCLASS()
class SHOOTING2D_API ACEnemy : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

public:	
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	float Speed = 700;

	FVector Direction;

protected:
	UPROPERTY(EditAnywhere)
	int32 RateTo = 30;
};
