// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    int32 PlayersDetected = AGameModeBase::GetNumPlayers();
    UE_LOG(LogTemp, Error, TEXT("Current players: %d"),PlayersDetected);

    if(PlayersDetected >= 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("3 players reached"));
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    int32 PlayersDetected = AGameModeBase::GetNumPlayers();
    UE_LOG(LogTemp, Error, TEXT("Current players: %d"),PlayersDetected);
}
