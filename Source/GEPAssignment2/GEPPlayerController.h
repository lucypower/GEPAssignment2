#pragma once

#include "CoreMinimal.h"
#include "MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "GEPPlayerController.generated.h"

class UInputMappingContext;

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

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _pawnToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"));
	TObjectPtr<UInputMappingContext> _defaultMappingContext; // is fine, rider error
};
