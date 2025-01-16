#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGameOverWidget.generated.h"

UCLASS()
class SHOOTING2D_API UCGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Restart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Quit;

public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();
};
