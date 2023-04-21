#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentDeadSignature, AController*, causer);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GEPASSIGNMENT2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Component")
	FComponentDeadSignature onComponentDead;

protected:

	// health
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float currentHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float maxHealth;
	
	// shield
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shield")
	float currentShield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shield")
	float maxShield;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shield")
	bool canRegenShield;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shield")
	float shieldRecoverDelayTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shield")
	float shieldRecoverRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shield")
	float shieldRecoverDelay;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION() // binding func as event, needs to be ufunc
	void DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType, AController* instigator, AActor* causer);
};
