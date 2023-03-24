// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBase, Display, All);


// Sets default values
AWeapon_Base::AWeapon_Base()
{
	_root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _root;

	_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_mesh->SetupAttachment(_root);

	_muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_muzzle->SetupAttachment(_mesh);
}

bool AWeapon_Base::Fire_Implementation()
{
	UE_LOG(LogWeaponBase, Display, TEXT("Firing Base weapon class"));
	return true;
}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

