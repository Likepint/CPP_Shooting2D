#include "CGameMode.h"

ACGameMode::ACGameMode()
{
	ConstructorHelpers::FClassFinder<APawn> pawn(L"/Script/Engine.Blueprint'/Game/PJS/Blueprints/BP_CSpaceship.BP_CSpaceship_C'");

	if (!!pawn.Succeeded())
	{
		//GEngine->AddOnScreenDebugMessage(0, 5, FColor::Cyan, L"Success");

		DefaultPawnClass = pawn.Class;
	}
}
