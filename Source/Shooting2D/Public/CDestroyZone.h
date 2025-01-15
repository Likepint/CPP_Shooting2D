#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDestroyZone.generated.h"

UCLASS()
class SHOOTING2D_API ACDestroyZone : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
public:	
	ACDestroyZone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

//private:
//	UFUNCTION()
//	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
