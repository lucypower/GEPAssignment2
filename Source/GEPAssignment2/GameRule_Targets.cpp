#include "GameRule_Targets.h"

#include "Target.h"
#include "Kismet/GameplayStatics.h"

UGameRule_Targets::UGameRule_Targets()
{
}

void UGameRule_Targets::Init()
{
	if (_Targets.Num() == 0)
	{
		TArray<AActor*> outActors;

		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("GameRuleTarget"), outActors);

		for (AActor* a : outActors)
		{
			_Targets.Add(Cast<UTarget>(a->GetComponentByClass(UTarget::StaticClass())));
		}
	}

	_AmountRemaining = _Targets.Num();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black,
		FString::Printf(TEXT("GameRule_Collectables: Found %d Collectables in World"), _AmountRemaining));
	
	for (UTarget* target : _Targets)
	{
		target->OnTargetDestroyed.AddDynamic(this, &UGameRule_Targets::Handle_TargetDestroyed);
	}
		
	Super::Init();
}

void UGameRule_Targets::Handle_TargetDestroyed(AActor* target, AController* causer)
{

	_AmountRemaining--;
	
	BroadcastGameRulePointsScored(causer, 1);

	if (_AmountRemaining == 0)
	{
		BroadcastGameRuleCompleted();
	}
}
