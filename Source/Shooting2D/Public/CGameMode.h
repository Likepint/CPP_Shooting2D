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
	// ����, �ε�
	// �ְ� ���� ���� �� ����
	void SaveGameData();
	// ������ ���� �� �ְ����� �ε�
	void LoadGameData();

public:
	void SetHP(float InCur, float InMax);

public:
	void AddScore(int32 InPoint); // { CurrentScore += InPoint; }

	void PrintCurrentScore();
	void PrintHighScore();

	void ShowGameOver(bool bShow);

private:
	// ���� �� ��Ʈ�� �ε�� ���� ����
	class UCMainWidget* MainUI;

private:
	// ���� ���� ����
	int32 CurrentScore = 0;

	// �ְ� ���� ����
	int32 HighScore = 0;

protected:
	// Slot Name
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Slot = L"HighScore";

	// UserIndex
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 UserIndex = 0;
};
