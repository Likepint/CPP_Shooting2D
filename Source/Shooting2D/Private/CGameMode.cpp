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
		// MainWidget 블루프린트 파일을 메모리에 로드
		MainUI = CreateWidget<UCMainWidget>(GetWorld(), MainWidget);

		// 위젯이 메모리에 로드되면 뷰 포트에 출력
		if (!!MainUI)
			MainUI->AddToViewport();
	}
}

// 현재 점수를 계산하는 함수
void ACGameMode::AddScore(int32 InPoint)
{
	// 현재 점수에 계속해서 누적
	CurrentScore += InPoint;

	PrintScore();
}

void ACGameMode::PrintScore()
{
	if (!!MainUI)
	{
		// ScoreData TextBlock에 현재 점수 값 입력
		MainUI->ScoreData->SetText(FText::AsNumber(CurrentScore));
	}
}
