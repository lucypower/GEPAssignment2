#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "GEPPlayerController.generated.h"

class UInputMappingContext;
class UWidget_Score;
class UWidget_GoalText;

UCLASS(Abstract)
class GEPASSIGNMENT2_API AGEPPlayerController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()

public:

	AGEPPlayerController();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Handle_MatchStarted_Implementation() override;

	virtual void Handle_MatchEnded_Implementation() override;

	void AddScore(int amount);

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _pawnToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Score> _scoreWidgetClass;

	TObjectPtr<UWidget_Score> _scoreWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_GoalText> _goalWidgetClass;

	TObjectPtr<UWidget_GoalText> _goalWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"));
	TObjectPtr<UInputMappingContext> _defaultMappingContext; // is fine, rider error

	int _score;
};
