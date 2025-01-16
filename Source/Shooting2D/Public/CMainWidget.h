#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainWidget.generated.h"

UCLASS()
class SHOOTING2D_API UCMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HighScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HighScoreData;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentScoreData;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCGameOverWidget* GameOverWidget;

public:
	// UI에서 사용하는 유사 BeginPlay()
	virtual void NativeConstruct() override;

public:
	void SetCurrentScore(int32 InNewScore);
	void SetHighScore(int32 InNewHightScore);
	void SetHP(float InCur, float InMax);

public:
	void ShowGameOver(bool bShow);
};
