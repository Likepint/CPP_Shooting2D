#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UCLASS()
class SHOOTING2D_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCMainWidget> MainWidget;

public:
	ACGameMode();

protected:
	virtual void BeginPlay() override;

private:
	// 저장, 로드
	// 최고 점수 갱신 시 저장
	void SaveGameData();
	// 게임이 시작 시 최고점수 로드
	void LoadGameData();

public:
	void SetHP(float InCur, float InMax);

public:
	void AddScore(int32 InPoint); // { CurrentScore += InPoint; }

	void PrintCurrentScore();
	void PrintHighScore();

	void ShowGameOver(bool bShow);

private:
	// 현재 뷰 포트에 로드된 위젯 저장
	class UCMainWidget* MainUI;

private:
	// 현재 점수 저장
	int32 CurrentScore = 0;

	// 최고 점수 저장
	int32 HighScore = 0;

protected:
	// Slot Name
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Slot = L"HighScore";

	// UserIndex
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 UserIndex = 0;
};
