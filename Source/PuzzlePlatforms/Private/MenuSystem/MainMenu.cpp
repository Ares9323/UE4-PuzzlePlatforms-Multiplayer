// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "MenuSystem/ServerRow.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/Optional.h"


UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UUserWidget> ServerRowWBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if(!ensure(ServerRowWBPClass.Class!=nullptr)) return;
	ServerRowClass = ServerRowWBPClass.Class;
	//UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *ServerRowClass->GetName());
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames)
{
    UWorld* World = this->GetWorld();
    if(!ensure(World!=nullptr)) return;

    ServerList->ClearChildren();

    uint32 i=0;
    for (const FServerData& ServerData : ServerNames)
    {
        UServerRow* Row = CreateWidget<UServerRow>(this,ServerRowClass);
        if(!ensure(Row!=nullptr)) return;

        Row->ServerName->SetText(FText::FromString(ServerData.Name));
        Row->HostUser->SetText(FText::FromString(ServerData.HostUsername));
        FText FractionText = FText::FromString(FString::Printf(TEXT("%d/%d"),ServerData.CurrentPlayers,ServerData.MaxPlayers));
        Row->ConnectionFraction->SetText(FractionText);
        Row->Setup(this,i);
        ++i;

        ServerList->AddChild(Row);
    }
}

void UMainMenu::SelectIndex(uint32 Index)
{
    SelectedIndex = Index;
    UpdateChildren();
}

uint32 UMainMenu::GetSelectedIndex()
{
    if (SelectedIndex.IsSet())
    {
        return SelectedIndex.GetValue();
    } else {
        return -1;
    }

}

bool UMainMenu::Initialize()
{
    // Return false if parent function failed
    bool Success = Super::Initialize();
    if(!Success) return false;

    // Open Host Menu
    if(!ensure(HostButton!=nullptr)) return false;
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);

    // Open Join Menu
    if(!ensure(JoinButton!=nullptr)) return false;
    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

    // Open Join List Menu
    if(!ensure(ServerListButton!=nullptr)) return false;
    ServerListButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinListMenu);

    // Return to Main Menu
    if(!ensure(CancelButton!=nullptr)) return false;
    CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
    if(!ensure(CancelJoinSessionButton!=nullptr)) return false;
    CancelJoinSessionButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
    if(!ensure(CancelHostingButton!=nullptr)) return false;
    CancelHostingButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

    // Quit Game
    if(!ensure(QuitButton!=nullptr)) return false;
    QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

    // Start Hosting a Server
    if(!ensure(StartHostingButton!=nullptr)) return false;
    StartHostingButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

    // Join Server
    if(!ensure(JoinServerButton!=nullptr)) return false;
    JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    // Join Server from list
    if(!ensure(JoinSessionButton!=nullptr)) return false;
    JoinSessionButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServerFromList);

    return true;

}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel,InWorld);

    this->RemoveFromViewport();

    UWorld* World = GetWorld();
    if(!ensure(World!=nullptr)) return;
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController!=nullptr)) return;

	FInputModeGameOnly InputModeData;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm gonna host a server!"));
    if(MenuInterface != nullptr)
    {
        FString ServerName = "Stocazzo";
        MenuInterface->Host(ServerName);
    }
}

void UMainMenu::OpenHostMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Opening host menu!"));
    if(!ensure(MenuSwitcher!=nullptr)) return;
    if(!ensure(HostMenu!=nullptr)) return;

    MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::OpenJoinMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Opening join menu!"));
    if(!ensure(MenuSwitcher!=nullptr)) return;
    if(!ensure(JoinMenu!=nullptr)) return;

    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenJoinListMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Opening server list menu!"));
    if(!ensure(MenuSwitcher!=nullptr)) return;
    if(!ensure(JoinMenuList!=nullptr)) return;

    MenuSwitcher->SetActiveWidget(JoinMenuList);
    if(MenuInterface!=nullptr)
    {
        MenuInterface->RefreshServerList();
    }
}

void UMainMenu::OpenMainMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("Back to main menu!"));
    if(!ensure(MenuSwitcher!=nullptr)) return;
    if(!ensure(MainMenu!=nullptr)) return;

    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm joining a server!"));
    if(MenuInterface != nullptr)
    {
        if(!ensure(IPAddressField!=nullptr)) return;
        const FString& Address = IPAddressField->GetText().ToString();
        MenuInterface->Join(Address);
    }
}

void UMainMenu::JoinServerFromList()
{
    UE_LOG(LogTemp, Warning, TEXT("I'm joining a server from a list!"));
    if(SelectedIndex.IsSet() && MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Selected index: %d"), SelectedIndex.GetValue());
        MenuInterface->JoinList(SelectedIndex.GetValue());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));
    }
}

void UMainMenu::QuitPressed()
{
    UWorld* World = GetWorld();
    if(!ensure(World!=nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController!=nullptr)) return;

    PlayerController->ConsoleCommand("quit");

}

void UMainMenu::UpdateChildren()
{
    for(int32 i=0; i<ServerList->GetChildrenCount(); ++i)
    {
        auto Row = Cast<UServerRow>(ServerList->GetChildAt(i));
        if(Row != nullptr)
        {
            Row->bSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
        }
    }
}
