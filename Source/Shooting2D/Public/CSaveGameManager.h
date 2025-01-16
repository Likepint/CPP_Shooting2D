#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSaveGameManager.generated.h"

UCLASS()
class SHOOTING2D_API UCSaveGameManager : public ULocalPlayerSaveGame
{
	GENERATED_BODY()
	
public:
	// �����ϰ� ���� ������ ���� ����
	UPROPERTY(BlueprintReadWrite)
	int32 SavedHighScoreData;
};
