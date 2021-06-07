// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"


USTRUCT()
struct FServerData
{
	GENERATED_USTRUCT_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};


/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer & ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	void SelectIndex(uint32 Index);
	uint32 GetSelectedIndex();

protected:
	virtual bool Initialize();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	TSubclassOf<class UUserWidget> ServerRowClass;


// Generic widgets

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

// Menus

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenuList;

// Main Menu Buttons

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerListButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

// Host Menu Buttons

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelHostingButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartHostingButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* ServerNameField;

// Join Menu Buttons

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* IPAddressField;

// Join Menu List Buttons

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelJoinSessionButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinSessionButton;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;


// Functions

	UFUNCTION(Category="Hosting")
	void HostServer();

	UFUNCTION(Category="Joining")
	void OpenHostMenu();

	UFUNCTION(Category="Joining")
	void OpenJoinMenu();

	UFUNCTION(Category="Joining")
	void OpenJoinListMenu();

	UFUNCTION(Category="Joining")
	void OpenMainMenu();

	UFUNCTION(Category="Joining")
	void JoinServer();

	UFUNCTION(Category="Joining")
	void JoinServerFromList();

	UFUNCTION(Category="Joining")
	void QuitPressed();

	TOptional<uint32> SelectedIndex;

	void UpdateChildren();

};



