#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UCLASS()
class SHOOTING2D_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACGameMode();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCMainWidget> MainWidget;

protected:
	virtual void BeginPlay() override;

public:
	void AddScore(int32 InPoint); // { CurrentScore += InPoint; }

	void PrintScore();

private:
	// 현재 뷰 포트에 로드된 위젯 저장
	class UCMainWidget* MainUI;

private:
	// 현재 점수 저장
	int32 CurrentScore = 0;
};
