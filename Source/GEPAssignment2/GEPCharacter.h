// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GEPCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class AWeapon_Base;

struct FInputActionValue;

UCLASS(Abstract)
class GEPASSIGNMENT2_API AGEPCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> _camera; // already exists in world

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "teu"))
	TObjectPtr<USceneComponent> _weaponAttachPoint; // already exists in world

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PlayerMappingContext; // reference to assets // error but cause rider hasn't caught up to new input system

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

public:
	// Sets default values for this character's properties
	AGEPCharacter();

	UFUNCTION(BlueprintNativeEvent)
	void Init();

protected:
	// Called when the game starts or when spawned
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _defaultWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> _fireableRef;
	

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void Shoot();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
