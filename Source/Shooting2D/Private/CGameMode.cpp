#include "CGameMode.h"
#include "CMainWidget.h"
#include "Components/TextBlock.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawn(L"/Script/Engine.Blueprint'/Game/PJS/Blueprints/BP_CSpaceship.BP_CSpaceship_C'");

	if (!!pawn.Succeeded())
	{
		//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, L"Success");

		DefaultPawnClass = pawn.Class;
	}
}

void ACGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!!MainWidget)
	{
		// MainWidget �������Ʈ ������ �޸𸮿� �ε�
		MainUI = CreateWidget<UCMainWidget>(GetWorld(), MainWidget);

		// ������ �޸𸮿� �ε�Ǹ� �� ��Ʈ�� ���
		if (!!MainUI)
			MainUI->AddToViewport();
	}
}

// ���� ������ ����ϴ� �Լ�
void ACGameMode::AddScore(int32 InPoint)
{
	// ���� ������ ����ؼ� ����
	CurrentScore += InPoint;

	PrintScore();
}

void ACGameMode::PrintScore()
{
	if (!!MainUI)
	{
		// ScoreData TextBlock�� ���� ���� �� �Է�
		MainUI->ScoreData->SetText(FText::AsNumber(CurrentScore));
	}
}
