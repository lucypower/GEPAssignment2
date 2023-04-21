#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameFramework/PlayerController.h"
#include "UObject/Object.h"
#include "GameRule_Collectables.generated.h"

class ACollectable;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GEPASSIGNMENT2_API UGameRule_Collectables : public UGameRule
{
	GENERATED_BODY()

public:

	UGameRule_Collectables();
	virtual void Init() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACollectable>> m_collectables;

	int m_amountRemaining;

	UFUNCTION()
	void Handle_Collected(ACollectable* subject, AController* causer); //TODO WHY PLAYER CONTROLLER NOT NORMAL CONTROLLER
};
