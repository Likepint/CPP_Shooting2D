#include "CGameOverWidget.h"
#include "Components/Button.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ��ư �Է� �̺�Ʈ�� �����ϴ� �Լ��� ����
	Button_Restart->OnClicked.AddDynamic(this, &UCGameOverWidget::Restart);
	Button_Quit->OnClicked.AddDynamic(this, &UCGameOverWidget::Quit);
}

void UCGameOverWidget::Restart()
{

}

void UCGameOverWidget::Quit()
{

}
