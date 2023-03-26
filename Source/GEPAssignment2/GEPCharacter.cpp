// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Fireable.h"
#include "Weapon_Base.h"

// Sets default values
AGEPCharacter::AGEPCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(GetCapsuleComponent());
	_camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	_camera->bUsePawnControlRotation = true;

	_weaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttachPoint"));
	_weaponAttachPoint->SetupAttachment(_camera);
}

void AGEPCharacter::Init_Implementation()
{
	if (_defaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;

		TObjectPtr<AActor> spawnedGun = GetWorld()->SpawnActor(_defaultWeapon, &_weaponAttachPoint->GetComponentTransform(), spawnParams);

		spawnedGun->AttachToComponent(_weaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

		if (UKismetSystemLibrary::DoesImplementInterface(spawnedGun, UFireable::StaticClass()))
		{
			_fireableRef = spawnedGun;
		}
	}
}

void AGEPCharacter::Move(const FInputActionValue& Value)
{
	FVector2D movementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), movementVector.Y);
		AddMovementInput(GetActorRightVector(), movementVector.X);
	}
}

void AGEPCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lookAxisVector.X);
		AddControllerPitchInput(lookAxisVector.Y);
	}
}

void AGEPCharacter::Shoot()
{
	if (_fireableRef)
	{
		IFireable::Execute_Fire(_fireableRef);
	}
}

// Called to bind functionality to input
void AGEPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		enhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGEPCharacter::Move);
		
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGEPCharacter::Look);
		
		enhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGEPCharacter::Shoot);
		
	}
}

