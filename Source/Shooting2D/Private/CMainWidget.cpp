#include "CMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "CGameOverWidget.h"

void UCMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHighScore(0);
	SetCurrentScore(0);
	ShowGameOver(false);
}

void UCMainWidget::SetCurrentScore(int32 InNewScore)
{
	CurrentScoreData->SetText(FText::AsNumber(InNewScore));
}

void UCMainWidget::SetHighScore(int32 InNewHightScore)
{
	HighScoreData->SetText(FText::AsNumber(InNewHightScore));
}

void UCMainWidget::SetHP(float InCur, float InMax)
{
	if (!!HPBar)
		HPBar->SetPercent(InCur / InMax);
}

void UCMainWidget::ShowGameOver(bool bShow)
{
	if (!!GameOverWidget)
	{
		//if (bShow)
		//	GameOverWidget->SetVisibility(ESlateVisibility::Visible);
		//else GameOverWidget->SetVisibility(ESlateVisibility::Hidden);

		GameOverWidget->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
