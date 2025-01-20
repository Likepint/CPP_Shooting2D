#include "CGameMode.h"
#include "CMainWidget.h"
#include "Components/TextBlock.h"
#include "CSaveGameManager.h"
#include "Kismet/GameplayStatics.h"

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

	if (!!BGM)
		UGameplayStatics::PlaySound2D(GetWorld(), BGM);

	// 저장되어 있는 데이터 로드
	LoadGameData();

	if (!!MainWidget)
	{
		// MainWidget 블루프린트 파일을 메모리에 로드
		MainUI = CreateWidget<UCMainWidget>(GetWorld(), MainWidget);

		// 위젯이 메모리에 로드되면 뷰 포트에 출력
		if (!!MainUI)
		{
			MainUI->AddToViewport();

			// 최고 점수 UI를 갱신
			MainUI->SetHighScore(HighScore);
		}
	}
}

void ACGameMode::SaveGameData()
{
	// SaveGameManager 객체 생성
	if (UCSaveGameManager* mgr = Cast<UCSaveGameManager>(UGameplayStatics::CreateSaveGameObject(UCSaveGameManager::StaticClass())))
	{
		// 객체에 SavedHighScoreData의 값을 HighScore로 갱신
		mgr->SavedHighScoreData = HighScore;

		// 데이터 파일 저장
		UGameplayStatics::SaveGameToSlot(mgr, Slot, UserIndex);
	}
}

void ACGameMode::LoadGameData()
{
	// 세이브 파일이 존재하는지 확인 후 있다면
	if (UGameplayStatics::DoesSaveGameExist(Slot, UserIndex))
	{
		// UCSaveGameManager 객체 생성
		UCSaveGameManager* mgr = Cast<UCSaveGameManager>(UGameplayStatics::LoadGameFromSlot(Slot, 0));

		if (mgr == nullptr) return;

		// 로드된 값을 최고 점수로 설정
		HighScore = mgr->SavedHighScoreData;
	}

	//if (UCSaveGameManager* mgr = Cast<UCSaveGameManager>(UGameplayStatics::LoadGameFromSlot(Slot, 0)))
	//{
	//	HighScore = mgr->SavedHighScoreData;
	//}
}

void ACGameMode::SetHP(float InCur, float InMax)
{
	if (!!MainUI)
		MainUI->SetHP(InCur, InMax);
}

// 현재 점수를 계산하는 함수
void ACGameMode::AddScore(int32 InPoint)
{
	// 현재 점수에 계속해서 누적
	CurrentScore += InPoint;

	PrintCurrentScore();

	// 현재 점수가 최고 점수를 초과
	if (CurrentScore > HighScore)
	{
		// 최고 점수를 현재 점수로 설정
		HighScore = CurrentScore;

		// 최고 점수 저장
		SaveGameData();

		// 최고 점수 UI를 갱신
		PrintHighScore();
	}
}

void ACGameMode::PrintCurrentScore()
{
	if (!!MainUI)
	{
		// ScoreData TextBlock에 현재 점수 값 입력
		//MainUI->CurrentScoreData->SetText(FText::AsNumber(CurrentScore));
		MainUI->SetCurrentScore(CurrentScore);
	}
}

void ACGameMode::PrintHighScore()
{
	if (!!MainUI)
		MainUI->SetHighScore(HighScore);
}

void ACGameMode::ShowGameOver(bool bShow)
{
	if (!!MainUI)
	{
		// bShow 값에 따라 게임 일시 정지 상태 설정
		UGameplayStatics::SetGamePaused(GetWorld(), bShow);

		// bShow 값에 따라 마우스 커서 표시/해제
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		controller->SetShowMouseCursor(bShow);

		// bShow 값에 따라 InputMode 설정
		if (bShow)
		{
			// 포커스를 UI에 고정
			controller->SetInputMode(FInputModeUIOnly());
		}
		else
		{
			// 포커스를 게임화면에 고정
			controller->SetInputMode(FInputModeGameOnly());
		}

		MainUI->ShowGameOver(bShow);
	}
}
