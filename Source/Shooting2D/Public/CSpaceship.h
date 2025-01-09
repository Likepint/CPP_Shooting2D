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
	// �����ͷ� �����ϸ� ���� ��
	// -> �����ͷ� �������� ������, �ش� ��������� ��Ŭ��� �ʿ�

	// �浹ü ������Ʈ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* Box;

	// ����ƽ �޽� ������Ʈ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

protected:
	// �̵�
	// P = P0 + v(direction * speed) * t
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 500.f;

//public:
//	// �ڷ���
//	// ����, �Ǽ�, ��, ���ڿ�
//	// int ���� ��� int32�� ���
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
//	int32 Num = 11;
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
//	float Distance = 3.14f;
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
//	bool bGood = true;
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Val")
//	FString MyName = L"parkejongsu";
//
//	UFUNCTION(BlueprintCallable)
//	// �������Ʈ���� ȣ�� ������ �Լ�
//	int32 MyAddCallable(int32 a, int32 b);
//
//	UFUNCTION(BlueprintPure)
//	// �������� ���� �����Լ�
//	int32 MyAddPure(int32 a, int32 b);
//
//	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
//	// �������Ʈ���� �����ϴ� �����Լ�
//	int32 MyAddImplementableEvent(int32 a, int32 b);
//
//	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
//	int32 MyAddNativeEvent(int32 a, int32 b);
//	int32 MyAddNativeEvent_Implementation(int32 a, int32 b);
};
