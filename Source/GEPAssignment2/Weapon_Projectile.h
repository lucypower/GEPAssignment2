// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GEPAssignment2Projectile.h"
#include "Weapon_Base.h"
#include "Weapon_Projectile.generated.h"

UCLASS(Abstract)
class GEPASSIGNMENT2_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGEPAssignment2Projectile> _Projectile;

public:

	virtual bool Fire_Implementation() override;
};
