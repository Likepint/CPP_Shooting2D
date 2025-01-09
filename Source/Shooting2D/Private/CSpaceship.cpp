#include "CSpaceship.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACSpaceship::ACSpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 컴포넌트를 Root 컴포넌트로 설정
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	// Box Extent 50
	Box->SetBoxExtent(FVector(50, 50, 50));

	// 스태틱 메시 컴포넌트를 Root 컴포넌트에 Attach
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Box);

	// 스태틱 메시 기본 큐브 설정
	ConstructorHelpers::FObjectFinder<UStaticMesh> cube(L"/Script/Engine.StaticMesh'/Game/PJS/Meshes/Cube.Cube'");
	if (!!cube.Succeeded())
		StaticMesh->SetStaticMesh(cube.Object);
}

void ACSpaceship::BeginPlay()
{
	Super::BeginPlay();
	
	//// Hello World / LOG
	//UE_LOG(LogTemp, Warning, L"Hello World");

	//// Debug Message
	//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, L"Hello World");

	//UE_LOG(LogTemp, Warning, TEXT("%d"), Num);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), bGood);

	//// 문자열
	//// FString : 문자열을 조합해서 생성, 주로 사용하는 문자열 자료형
	//// FText, FName
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *MyName);

}

void ACSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{   // 오른쪽으로 이동
	    // P = P0 + v(direction * speed) * t
		FVector p0 = GetActorLocation();
		FVector v = GetActorRightVector() * Speed;

		SetActorLocation(p0 + v * DeltaTime);
	}
}

void ACSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//int32 ACSpaceship::MyAddCallable(int32 a, int32 b)
//{
//
//	return a + b;
//}
//
//int32 ACSpaceship::MyAddPure(int32 a, int32 b)
//{
//
//	return a + b;
//}
//
//int32 ACSpaceship::MyAddNativeEvent_Implementation(int32 a, int32 b)
//{
//	return a + b;
//}
