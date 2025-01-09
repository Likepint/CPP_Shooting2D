#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CSpaceship.generated.h"

UCLASS()
class SHOOTING2D_API ACSpaceship : public APawn
{
	GENERATED_BODY()

public:
	ACSpaceship();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// �ڷ���
	// ����, �Ǽ�, ��, ���ڿ�
	// int ���� ��� int32�� ���
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
	int32 Num = 11;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
	float Distance = 3.14f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
	bool bGood = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
	FString MyName = L"parkejongsu";

};
