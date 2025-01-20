#include "CGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ��ư �Է� �̺�Ʈ�� �����ϴ� �Լ��� ����
	Button_Restart->OnClicked.AddDynamic(this, &UCGameOverWidget::Restart);
	Button_Quit->OnClicked.AddDynamic(this, &UCGameOverWidget::Quit);
}

void UCGameOverWidget::Restart()
{
	// ���� ������ �̸�
	FString lv = UGameplayStatics::GetCurrentLevelName(GetWorld());
	// ���� ���ε�
	UGameplayStatics::OpenLevel(GetWorld(), *lv);
}

void UCGameOverWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}
