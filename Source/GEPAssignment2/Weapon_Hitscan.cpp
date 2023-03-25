// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponHitscan, Display, All);

bool AWeapon_Hitscan::Fire_Implementation()
{
	UE_LOG(LogWeaponHitscan, Display, TEXT("Firing hitscan weapon class"));

	UWorld* const world = GetWorld();
	if (world == nullptr) { return false; }

	FHitResult hit(ForceInit);
	FVector start = _muzzle->GetComponentLocation();
	FVector end = start + (_muzzle->GetForwardVector() * 1000);
	TArray<AActor*> actorsToIgnore;

	if (UKismetSystemLibrary::LineTraceSingle(world, start, end, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, actorsToIgnore,
		EDrawDebugTrace::ForDuration, hit, true, FLinearColor::Red, FLinearColor::Green, 5))
	{
		//damage applying code
		UE_LOG(LogWeaponHitscan, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString());
	}

	return true;
}
