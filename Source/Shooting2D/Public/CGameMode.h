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
	// ���� �� ��Ʈ�� �ε�� ���� ����
	class UCMainWidget* MainUI;

private:
	// ���� ���� ����
	int32 CurrentScore = 0;
};
