#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS(Abstract)
class GEPASSIGNMENT2_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_radius = 100.0f;

	
	

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
