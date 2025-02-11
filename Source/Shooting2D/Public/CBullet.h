#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

UCLASS()
class SHOOTING2D_API ACBullet : public AActor
{
	GENERATED_BODY()

public:
	// Box Collision
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	// Static Mesh Component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

private:
	UPROPERTY(EditAnywhere)
	class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplosionVFX;
	
public:	
	ACBullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetActive(bool bInVal);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	float Speed = 1000;
};
