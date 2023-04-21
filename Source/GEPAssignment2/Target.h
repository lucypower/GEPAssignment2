#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Target.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTargetDestroyedSignature, AActor*, target, AController*, delegateInstigator);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GEPASSIGNMENT2_API UTarget : public UActorComponent
{
	GENERATED_BODY()

public:

	UTarget();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnTargetDestroyed;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _HealthComp;

private:

	UFUNCTION()
	void Handle_Dead(AController* causer);
};
