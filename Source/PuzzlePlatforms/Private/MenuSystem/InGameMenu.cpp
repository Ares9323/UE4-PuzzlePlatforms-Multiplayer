// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/InGameMenu.h"
#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
    // Return false if parent function failed
    bool Success = Super::Initialize();
    if(!Success) return false;

    // Return to Game
    if(!ensure(CancelButton!=nullptr)) return false;
    CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

    // Open Main Menu
    if(!ensure(QuitButton!=nullptr)) return false;
    QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

    return true;
}

void UInGameMenu::CancelPressed()
{
    Teardown();
}

void UInGameMenu::QuitPressed()
{
    if(MenuInterface != nullptr)
    {
        Teardown();
        MenuInterface->LoadMainMenu();
    }
}
