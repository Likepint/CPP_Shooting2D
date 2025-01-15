#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainWidget.generated.h"

UCLASS()
class SHOOTING2D_API UCMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreData;
};
