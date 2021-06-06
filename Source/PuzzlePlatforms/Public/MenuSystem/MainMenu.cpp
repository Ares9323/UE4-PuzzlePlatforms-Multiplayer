// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"

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

void UMainMenu::HostServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));
}

void UMainMenu::JoinServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm joining a server!"));
}
