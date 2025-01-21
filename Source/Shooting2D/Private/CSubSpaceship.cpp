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

	// ������ �̺�Ʈ ����
	Box->SetGenerateOverlapEvents(false);
	// ��� ä���� �浹 ���� ����
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
		CurrentTime += DeltaTime; // �ð� ����

		if (CurrentTime >= FireTime) // ���� �ð��� �߻� �ð��� �Ǹ�
		{
			MakeBullet(); // �Ѿ� ����

			CurrentTime = 0; // ���� �ð� �ʱ�ȭ
		}
	}
	else
	{
		if (!!Target)
		{
			// ���� ��ġ �� Y��(��/��)�� ���� ���� �� ��ġ�� �����ϰ� ����
			FVector CurPos = FVector(0, Target->GetComponentLocation().Y, GetActorLocation().Z);

			FVector dir = Target->GetComponentLocation() - CurPos;
			//FVector dir = Target->GetComponentLocation() - GetActorLocation();

			if (dir.Length() > 5)
			{
				FVector p0 = CurPos;
				FVector vt = dir.GetSafeNormal() * MoveToTargetSpeed * DeltaTime;

				SetActorLocation(p0 + vt);

				// ������ ���� ���ۺ��� ȸ��
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
