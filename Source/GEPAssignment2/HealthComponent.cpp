#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	maxHealth = 100.f;
	maxShield = 100.f;
	canRegenShield = true;
	shieldRecoverRate = 10.f;
	shieldRecoverDelay = 2.f;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	currentHealth = maxHealth;
	currentShield = maxShield;		
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damageTaken, const UDamageType* damageType,
	AController* instigator, AActor* causer)
{
	float leftOverDamage = FMath::Max(damageTaken - currentShield, 0.f);
	currentShield = FMath::Max(currentShield - damageTaken, 0.f);
	shieldRecoverDelayTimer = shieldRecoverDelay;

	if (leftOverDamage > 0.f) {currentHealth = FMath::Max(currentHealth - leftOverDamage, 0.f); }

	if (currentHealth <= 0.f) {onComponentDead.Broadcast(instigator); }
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (currentShield == maxHealth || !canRegenShield) {return; }	
	
	if (shieldRecoverDelayTimer > 0.f)
	{
		shieldRecoverDelayTimer -= DeltaTime;
	}
	else
	{
		currentShield = FMath::Min(maxShield, currentShield + (shieldRecoverRate * DeltaTime));
	}
}

