#include "GameRule_Collectables.h"

#include "Collectable.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UGameRule_Collectables::UGameRule_Collectables()
{
	m_amountRemaining = 0;
}

void UGameRule_Collectables::Init()
{

	if(m_collectables.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectable::StaticClass(), outActors);

		for(AActor* a : outActors)
		{
			m_collectables.Add(Cast<ACollectable>(a));
		}
	}

	m_amountRemaining = m_collectables.Num();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black,
		FString::Printf(TEXT("GameRule_Collectables: Found %d Collectables in World"), m_amountRemaining));

	for (ACollectable* col : m_collectables)
	{
		col->OnCollected.AddDynamic(this, &UGameRule_Collectables::Handle_Collected);
	}
	
	Super::Init();
}

void UGameRule_Collectables::Handle_Collected(ACollectable* subject, AController* causer)
{
	m_amountRemaining--;

	BroadcastGameRulePointsScored(causer, 1);

	if (m_amountRemaining == 0)
	{
		BroadcastGameRuleCompleted();
	}
}
