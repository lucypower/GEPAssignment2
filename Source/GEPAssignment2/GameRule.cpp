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
	OnGameRulePointsScored.Broadcast(scorer, points);
}


