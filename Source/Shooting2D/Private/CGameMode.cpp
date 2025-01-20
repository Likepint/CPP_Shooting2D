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

	// ����Ǿ� �ִ� ������ �ε�
	LoadGameData();

	if (!!MainWidget)
	{
		// MainWidget �������Ʈ ������ �޸𸮿� �ε�
		MainUI = CreateWidget<UCMainWidget>(GetWorld(), MainWidget);

		// ������ �޸𸮿� �ε�Ǹ� �� ��Ʈ�� ���
		if (!!MainUI)
		{
			MainUI->AddToViewport();

			// �ְ� ���� UI�� ����
			MainUI->SetHighScore(HighScore);
		}
	}
}

void ACGameMode::SaveGameData()
{
	// SaveGameManager ��ü ����
	if (UCSaveGameManager* mgr = Cast<UCSaveGameManager>(UGameplayStatics::CreateSaveGameObject(UCSaveGameManager::StaticClass())))
	{
		// ��ü�� SavedHighScoreData�� ���� HighScore�� ����
		mgr->SavedHighScoreData = HighScore;

		// ������ ���� ����
		UGameplayStatics::SaveGameToSlot(mgr, Slot, UserIndex);
	}
}

void ACGameMode::LoadGameData()
{
	// ���̺� ������ �����ϴ��� Ȯ�� �� �ִٸ�
	if (UGameplayStatics::DoesSaveGameExist(Slot, UserIndex))
	{
		// UCSaveGameManager ��ü ����
		UCSaveGameManager* mgr = Cast<UCSaveGameManager>(UGameplayStatics::LoadGameFromSlot(Slot, 0));

		if (mgr == nullptr) return;

		// �ε�� ���� �ְ� ������ ����
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

// ���� ������ ����ϴ� �Լ�
void ACGameMode::AddScore(int32 InPoint)
{
	// ���� ������ ����ؼ� ����
	CurrentScore += InPoint;

	PrintCurrentScore();

	// ���� ������ �ְ� ������ �ʰ�
	if (CurrentScore > HighScore)
	{
		// �ְ� ������ ���� ������ ����
		HighScore = CurrentScore;

		// �ְ� ���� ����
		SaveGameData();

		// �ְ� ���� UI�� ����
		PrintHighScore();
	}
}

void ACGameMode::PrintCurrentScore()
{
	if (!!MainUI)
	{
		// ScoreData TextBlock�� ���� ���� �� �Է�
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
		// bShow ���� ���� ���� �Ͻ� ���� ���� ����
		UGameplayStatics::SetGamePaused(GetWorld(), bShow);

		// bShow ���� ���� ���콺 Ŀ�� ǥ��/����
		APlayerController* controller = GetWorld()->GetFirstPlayerController();
		controller->SetShowMouseCursor(bShow);

		// bShow ���� ���� InputMode ����
		if (bShow)
		{
			// ��Ŀ���� UI�� ����
			controller->SetInputMode(FInputModeUIOnly());
		}
		else
		{
			// ��Ŀ���� ����ȭ�鿡 ����
			controller->SetInputMode(FInputModeGameOnly());
		}

		MainUI->ShowGameOver(bShow);
	}
}
