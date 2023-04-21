﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCollectedSignature, class ACollectable*, subject, AController*, causer);

class USphereComponent;

UCLASS(Abstract)
class GEPASSIGNMENT2_API ACollectable : public AActor
{
	GENERATED_BODY()

public:
	
	ACollectable();

	UPROPERTY(BlueprintAssignable)
	FCollectedSignature OnCollected;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> m_collision;

	UFUNCTION(BlueprintCallable)
	void BroadcastCollected(AController* causer);
};
