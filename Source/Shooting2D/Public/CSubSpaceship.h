#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSubSpaceship.generated.h"

UCLASS()
class SHOOTING2D_API ACSubSpaceship : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* Arrow;
	
public:	
	ACSubSpaceship();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void MakeBullet();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ACBullet> BulletFactory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentTime = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FireTime = 0.2;

	UPROPERTY(EditAnywhere)
	bool bStartFire = false;

public:
	UPROPERTY(EditAnywhere)
	class USceneComponent* Target;

	UPROPERTY(EditAnywhere)
	float MoveToTargetSpeed = 700;
};
