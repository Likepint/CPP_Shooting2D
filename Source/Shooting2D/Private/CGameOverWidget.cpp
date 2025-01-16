#include "CGameOverWidget.h"
#include "Components/Button.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼 입력 이벤트에 대응하는 함수를 연결
	Button_Restart->OnClicked.AddDynamic(this, &UCGameOverWidget::Restart);
	Button_Quit->OnClicked.AddDynamic(this, &UCGameOverWidget::Quit);
}

void UCGameOverWidget::Restart()
{

}

void UCGameOverWidget::Quit()
{

}
