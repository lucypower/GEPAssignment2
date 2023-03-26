// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "GEPCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


AGEPPlayerController::AGEPPlayerController() : Super()
{
	
}

void AGEPPlayerController::Init_Implementation()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(_defaultMappingContext, 0);
	}

	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
}

void AGEPPlayerController::Handle_MatchStarted_Implementation()
{
	UWorld* const world = GetWorld();

	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	
	FVector spawnLocation = tempStart != nullptr ? tempStart->GetActorLocation() : FVector::ZeroVector; // if tempstart not nullptr, getactorlocation, otherwise return vector.zero
	FRotator spawnRotation = tempStart != nullptr ? tempStart->GetActorRotation() : FRotator::ZeroRotator;

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* tempPawn = world->SpawnActor<APawn>(_pawnToSpawn, spawnLocation, spawnRotation, spawnParams);
	Possess(tempPawn);

	if (AGEPCharacter* castedPawn = Cast<AGEPCharacter>(tempPawn))
	{
		// TODO: Bind to any relevant events

		castedPawn->Init();
	}
}

void AGEPPlayerController::Handle_MatchEnded_Implementation()
{
	// SetInputMode(FInputModeUIOnly());
}
