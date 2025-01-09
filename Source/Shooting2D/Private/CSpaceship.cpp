#include "CSpaceship.h"

ACSpaceship::ACSpaceship()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ACSpaceship::BeginPlay()
{
	Super::BeginPlay();
	
	// Hello World / LOG
	UE_LOG(LogTemp, Warning, L"Hello World");

	// Debug Message
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, L"Hello World");

	UE_LOG(LogTemp, Warning, TEXT("%d"), Num);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bGood);

	// ���ڿ�
	// FString : ���ڿ��� �����ؼ� ����, �ַ� ����ϴ� ���ڿ� �ڷ���
	// FText, FName
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyName);

}

void ACSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
