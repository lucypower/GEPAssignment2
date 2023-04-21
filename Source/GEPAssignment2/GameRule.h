#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleCompletedSignature, class UGameRule*, rule);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointsScoredSignature, AController*, scorer, int, points);

UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GEPASSIGNMENT2_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:

	UGameRule();

	FGameRuleCompletedSignature OnGameRuleCompleted;
	FGameRulePointsScoredSignature OnGameRulePointsScored;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool m_isOptional;

	UFUNCTION()
	virtual void Init();

protected:

	void BroadcastGameRuleCompleted();
	void BroadcastGameRulePointsScored(AController* scorer, int points);
};
