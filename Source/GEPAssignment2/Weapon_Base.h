﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fireable.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class USkeletalMeshComponent;
class UArrowComponent;

UCLASS(Abstract)
class GEPASSIGNMENT2_API AWeapon_Base : public AActor, public IFireable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon_Base();

	virtual bool Fire_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _root;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _mesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _muzzle;
};
