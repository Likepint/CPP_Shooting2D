#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyFactory.generated.h"

UCLASS()
class SHOOTING2D_API ACEnemyFactory : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* Arrow;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemy> Enemy;
	
public:	
	ACEnemyFactory();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnEnemy();

private:
	FTimerHandle TimerHandle;

	float DelayTime = 0;
	float SpawnTime = 0.5;
};
