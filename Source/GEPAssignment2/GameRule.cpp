#include "GameRule.h"

UGameRule::UGameRule()
{
	m_isOptional = false;
}

void UGameRule::Init()
{
	
}

void UGameRule::BroadcastGameRuleCompleted()
{

	OnGameRuleCompleted.Broadcast(this);
}

void UGameRule::BroadcastGameRulePointsScored(AController* scorer, int points)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black,
FString::Printf(TEXT("GameRule_Collectables: DONE!!")));
	OnGameRulePointsScored.Broadcast(scorer, points);
}


