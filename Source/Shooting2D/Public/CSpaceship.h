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
	// 포인터로 생성하면 좋은 점
	// -> 포인터로 생성하지 않으면, 해당 헤더파일을 인클루드 필요

	// 충돌체 컴포넌트
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* Box;

	// 스태틱 메시 컴포넌트
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UArrowComponent* Arrow;

	// 서브 기체
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UArrowComponent* Sub_L;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UArrowComponent* Sub_R;

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

	// 데미지 처리
	void OnDamaged(int32 InDamage); // 적이 호출

//private:
//	UFUNCTION()
//	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	class ACSubSpaceship* SubFlight_L;

	UPROPERTY(EditAnywhere)
	class ACSubSpaceship* SubFlight_R;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACBullet> BulletFactory;

	UPROPERTY(EditAnywhere)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACSubSpaceship> SubFlightFactory;

protected:
	// 이동
	// P = P0 + v(direction * speed) * t
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 500.f;

	float Vertical;
	float Horizontal;

	// 최대 체력
	UPROPERTY(EditAnywhere)
	float MaxHP = 2;

	UPROPERTY(EditAnywhere)
	float FireTime = 0.2f;

private:
	// 현재 체력
	float CurHP;

	// 총알 오브젝트 풀 처리
	// [ 필요 요소 ]
	// - 최초 생성할 총알 갯수
	UPROPERTY(EditAnywhere)
	int32 MaxBulletCount = 20;

	// - 총알 목록
	UPROPERTY(EditAnywhere)
	TArray<class ACBullet*> Magazine;

	// 자동 발사 기능
	UPROPERTY(VisibleAnywhere)
	bool bAutoFire = false;
	float CurrentTime = 0;

//public:
//	// 자료형
//	// 정수, 실수, 논리, 문자열
//	// int 형의 경우 int32로 사용
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
//	// 블루프린트에서 호출 가능한 함수
//	int32 MyAddCallable(int32 a, int32 b);
//
//	UFUNCTION(BlueprintPure)
//	// 실행핀이 없는 순수함수
//	int32 MyAddPure(int32 a, int32 b);
//
//	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
//	// 블루프린트에서 구현하는 가상함수
//	int32 MyAddImplementableEvent(int32 a, int32 b);
//
//	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
//	int32 MyAddNativeEvent(int32 a, int32 b);
//	int32 MyAddNativeEvent_Implementation(int32 a, int32 b);
};
