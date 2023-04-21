// Copyright Epic Games, Inc. All Rights Reserved.

#include "GEPAssignment2GameMode.h"

#include "GameRule.h"
#include "GEPAssignment2Character.h"
#include "GEPPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AGEPAssignment2GameMode::AGEPAssignment2GameMode()
	: Super()
{
	_countdownTimer = 3;

	_GameRulesLeft = 0;
}

AActor* AGEPAssignment2GameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (_playerStarts.Num() == 0) // .num = .length
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), _playerStarts);
	}

	if (_playerStarts.Num() > 0)
	{
		return _playerStarts[0];
	}
	return nullptr;
}

void AGEPAssignment2GameMode::PostLogin(APlayerController* NewPlayer)
{
	_playerControllers.AddUnique(NewPlayer);

	if (AGEPPlayerController* castedPC = Cast<AGEPPlayerController>(NewPlayer))
	{
		// TODO: Bind to any relevant events

		castedPC->Init();
	}
	
	Super::PostLogin(NewPlayer);
}

void AGEPAssignment2GameMode::Logout(AController* Exiting)
{
	_playerControllers.Remove(Exiting);
	
	Super::Logout(Exiting);
}

void AGEPAssignment2GameMode::DecreaseCountdown()
{
	_countdownTimer--;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), _countdownTimer));

	if (_countdownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_timerDecreaseCountdown, this, &AGEPAssignment2GameMode::DecreaseCountdown, 1.f, false);
	}
}

void AGEPAssignment2GameMode::Handle_GameRuleCompleted(UGameRule* rule)
{
	if (*_GameRuleManagers.Find(rule)) { return; }

	_GameRulesLeft--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black,
		FString::Printf(TEXT("GameRule completed. %d Remaining!"),  _GameRulesLeft));

	if (_GameRulesLeft != 0) { return; }

	EndMatch();
}

void AGEPAssignment2GameMode::Handle_GameRulePointsScored(AController* scorer, int points)
{
}

void AGEPAssignment2GameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);

	for (UActorComponent* comp : outComponents)
	{
		if (UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule, rule->m_isOptional);
			
			rule->Init();
			rule->OnGameRuleCompleted.AddDynamic(this, &AGEPAssignment2GameMode::Handle_GameRuleCompleted);
			rule->OnGameRulePointsScored.AddDynamic(this, &AGEPAssignment2GameMode::Handle_GameRulePointsScored);

			if (!rule->m_isOptional)
			{
				_GameRulesLeft++;
			}
		}
	}
}

void AGEPAssignment2GameMode::HandleMatchIsWaitingToStart()
{
	GetWorld()->GetTimerManager().SetTimer(_timerDecreaseCountdown, this, &AGEPAssignment2GameMode::DecreaseCountdown, 1.f, false);
	
	Super::HandleMatchIsWaitingToStart();
}

void AGEPAssignment2GameMode::HandleMatchHasStarted()
{
	for (AController* controller : _playerControllers)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);			
		}
	}
	
	Super::HandleMatchHasStarted();
}

void AGEPAssignment2GameMode::HandleMatchHasEnded()
{
	for (AController* controller : _playerControllers)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(controller);			
		}
	}
	
	Super::HandleMatchHasEnded();
}

void AGEPAssignment2GameMode::OnMatchStateSet()
{
	FString output;

	if (MatchState == MatchState::WaitingToStart)
	{
		output = "Waiting to Start";
	}
	else if (MatchState == MatchState::InProgress)
	{
		output = "In Progress";
	}
	else if (MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting Post Match";
	}
	else if (MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString::Printf(TEXT("State Changed to: %s"), *output));
	
	Super::OnMatchStateSet();
}

bool AGEPAssignment2GameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AGEPAssignment2GameMode::ReadyToEndMatch_Implementation()
{
	return false;
}
