// Fill out your copyright notice in the Description page of Project Settings.


#include "GEPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "GEPCharacter.h"
#include "Widget_GoalText.h"
#include "Widget_Score.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


AGEPPlayerController::AGEPPlayerController() : Super()
{
	_score = 0;
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

	if (_scoreWidgetClass)
	{
		_scoreWidget = CreateWidget<UWidget_Score, AGEPPlayerController*>(this, _scoreWidgetClass);
		_scoreWidget->AddToViewport();
	}

	if (_goalWidgetClass)
	{
		_goalWidget = CreateWidget<UWidget_GoalText, AGEPPlayerController*>(this, _goalWidgetClass);
		_goalWidget->AddToViewport();
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

void AGEPPlayerController::AddScore(int amount)
{
	_score += amount;

	if (_scoreWidget != nullptr)
	{
		_scoreWidget->UpdateScore(_score);
	}
}
