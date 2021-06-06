// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "MenuSystem/MainMenu.h"



UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
	ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/_Main/BP_PlatformTrigger"));
	if(!ensure(PlatformTriggerBPClass.Class!=nullptr)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *PlatformTriggerBPClass.Class->GetName());

	ConstructorHelpers::FClassFinder<UUserWidget> MenuWBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(!ensure(MenuWBPClass.Class!=nullptr)) return;
	MenuClass = MenuWBPClass.Class;
	//UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
}


void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init()"));
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if(!ensure(MenuClass!=nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this,MenuClass);

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	if(Menu != nullptr)
	{
		//Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if(!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,2.f, FColor::Green, TEXT("HOSTING!"));
	UE_LOG(LogTemp, Warning, TEXT("HOSTING"));

	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if(!ensure(Engine!=nullptr)) return;

	Engine->AddOnScreenDebugMessage(0,5.f, FColor::Green, FString::Printf(TEXT("Joining %s!"), *Address));
	UE_LOG(LogTemp, Warning, TEXT("HOSTING"));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(!ensure(PlayerController!=nullptr)) return;

	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
}
