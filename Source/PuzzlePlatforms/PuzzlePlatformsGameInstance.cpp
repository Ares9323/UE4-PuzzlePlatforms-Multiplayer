// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
//#include "EngineGlobals.h"
#include "Engine.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Error, TEXT("GameInstance Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Error, TEXT("GameInstance Init()"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,2.f, FColor::Green, TEXT("HOSTING!"));
	UE_LOG(LogTemp, Error, TEXT("HOSTING"));

	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,5.f, FColor::Green, FString::Printf(TEXT("Joining %s!"), *Address));
	UE_LOG(LogTemp, Error, TEXT("HOSTING"));
}
