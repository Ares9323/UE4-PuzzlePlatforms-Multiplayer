// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatforms/MenuSystem/MainMenu.h"
#include <Components/Button.h>
#include <Components/WidgetSwitcher.h>
#include <Components/EditableTextBox.h>

bool UMainMenu::Initialize()
{
    // Return false if parent function failed
    bool Success = Super::Initialize();
    if(!Success) return false;

    // Host OnClick event
    if(!ensure(Host!=nullptr)) return false;
    Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

    // Host OnClick event
    if(!ensure(Join!=nullptr)) return false;
    Join->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    return true;


}

void UMainMenu::Setup()
{
    this->AddToViewport();

    UWorld* World = GetWorld();
    if(!ensure(World!=nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController!=nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* CurrentMenuInterface)
{
    this->MenuInterface = CurrentMenuInterface;
}

void UMainMenu::HostServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));
    if(MenuInterface != nullptr)
    {
        MenuInterface->Host();
    }
}

void UMainMenu::JoinServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm joining a server!"));
}
