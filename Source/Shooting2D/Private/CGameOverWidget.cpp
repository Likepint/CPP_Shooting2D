#include "CGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼 입력 이벤트에 대응하는 함수를 연결
	Button_Restart->OnClicked.AddDynamic(this, &UCGameOverWidget::Restart);
	Button_Quit->OnClicked.AddDynamic(this, &UCGameOverWidget::Quit);
}

void UCGameOverWidget::Restart()
{
	// 현재 레벨의 이름
	FString lv = UGameplayStatics::GetCurrentLevelName(GetWorld());
	// 레벨 리로드
	UGameplayStatics::OpenLevel(GetWorld(), *lv);
}

void UCGameOverWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}
