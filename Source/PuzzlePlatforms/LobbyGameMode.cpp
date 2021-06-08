// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "TimerManager.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    int32 PlayersDetected = AGameModeBase::GetNumPlayers();
    UE_LOG(LogTemp, Error, TEXT("Current players: %d"),PlayersDetected);

    if(PlayersDetected >= 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("2 players reached, moving to main map in 5 seconds"));
        GetWorldTimerManager().SetTimer(GameStartTimer,this,&ALobbyGameMode::StartGame,5);
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    int32 PlayersDetected = AGameModeBase::GetNumPlayers();
    UE_LOG(LogTemp, Error, TEXT("Current players: %d"),PlayersDetected);
}

void ALobbyGameMode::StartGame()
{
    UWorld* World = GetWorld();
    if(!ensure(World!=nullptr)) return;
    bUseSeamlessTravel = true;
    World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game?listen");
}
