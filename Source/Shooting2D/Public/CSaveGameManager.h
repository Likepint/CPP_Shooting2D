#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSaveGameManager.generated.h"

UCLASS()
class SHOOTING2D_API UCSaveGameManager : public ULocalPlayerSaveGame
{
	GENERATED_BODY()
	
public:
	// 저장하고 값을 저장할 변수 생성
	UPROPERTY(BlueprintReadWrite)
	int32 SavedHighScoreData;
};
