#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CSpaceship.generated.h"

UCLASS()
class SHOOTING2D_API ACSpaceship : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ACGameMode* GM;

public:
	// �����ͷ� �����ϸ� ���� ��
	// -> �����ͷ� �������� ������, �ش� ��������� ��Ŭ��� �ʿ�

	// �浹ü ������Ʈ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* Box;

	// ����ƽ �޽� ������Ʈ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UArrowComponent* Arrow;

public:
	ACSpaceship();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MakeBullet();

protected:
	void OnAxisVertical(float InVal);
	void OnAxisHorizontal(float InVal);

	void OnFire();
	void OnAutoFireClick();
	void OnAutoFirePressed();

public:
	float GetCurHP() { return CurHP; }

	// ������ ó��
	void OnDamaged(int32 InDamage); // ���� ȣ��

//private:
//	UFUNCTION()
//	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACBullet> BulletFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

protected:
	// �̵�
	// P = P0 + v(direction * speed) * t
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 500.f;

	float Vertical;
	float Horizontal;

	// �ִ� ü��
	UPROPERTY(EditAnywhere)
	float MaxHP = 2;

	UPROPERTY(EditAnywhere)
	float FireTime = 0.2f;

private:
	// ���� ü��
	float CurHP;

	// �Ѿ� ������Ʈ Ǯ ó��
	// [ �ʿ� ��� ]
	// - ���� ������ �Ѿ� ����
	UPROPERTY(EditAnywhere)
	int32 MaxBulletCount = 20;

	// - �Ѿ� ���
	UPROPERTY(EditAnywhere)
	TArray<class ACBullet*> Magazine;

	// �ڵ� �߻� ���
	UPROPERTY(VisibleAnywhere)
	bool bAutoFire = false;
	float CurrentTime = 0;

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
