#include "CSubSpaceship.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "CBullet.h"

ACSubSpaceship::ACSubSpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);
	// Extent 25
	Box->SetBoxExtent(FVector(25));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetRelativeScale3D(FVector(0.5));

	Arrow = CreateDefaultSubobject<UArrowComponent>("FirePosition");
	Arrow->SetupAttachment(RootComponent);
	Arrow->SetRelativeLocation(FVector(0, 0, 50));
	Arrow->SetRelativeRotation(FQuat(FRotator(90, 0, 0)));

	// 오버랩 이벤트 끄기
	Box->SetGenerateOverlapEvents(false);
	// 모든 채널의 충돌 무시 설정
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ACSubSpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACSubSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartFire)
	{
		CurrentTime += DeltaTime; // 시간 누적

		if (CurrentTime >= FireTime) // 누적 시간이 발사 시간이 되면
		{
			MakeBullet(); // 총알 생성

			CurrentTime = 0; // 현재 시간 초기화
		}
	}
	else
	{
		if (!!Target)
		{
			// 현재 위치 중 Y값(좌/우)를 내가 도착 할 위치와 동일하게 설정
			FVector CurPos = FVector(0, Target->GetComponentLocation().Y, GetActorLocation().Z);

			FVector dir = Target->GetComponentLocation() - CurPos;
			//FVector dir = Target->GetComponentLocation() - GetActorLocation();

			if (dir.Length() > 5)
			{
				FVector p0 = CurPos;
				FVector vt = dir.GetSafeNormal() * MoveToTargetSpeed * DeltaTime;

				SetActorLocation(p0 + vt);

				// 연출을 위한 빙글빙글 회전
				FRotator rot = StaticMesh->GetRelativeRotation();
				rot.Yaw += 10.f;
				StaticMesh->SetRelativeRotation(rot);
			}
			else
			{
				FRotator rot = StaticMesh->GetRelativeRotation();
				rot.Yaw = 0;
				StaticMesh->SetRelativeRotation(rot);

				bStartFire = true;

				FAttachmentTransformRules rules = FAttachmentTransformRules::KeepRelativeTransform;
				this->AttachToComponent(Target, rules);

				SetActorLocation(Target->GetComponentLocation());
			}
		}
	}
}

void ACSubSpaceship::MakeBullet()
{
	FTransform position = Arrow->GetComponentTransform();

	GetWorld()->SpawnActor<ACBullet>(BulletFactory, position);
}
