// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();
	void Teardown(); // No Longer Used

	void stocazzo();


protected:
	virtual bool Initialize();
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UFUNCTION(Category="Hosting")
	void HostServer();

	UFUNCTION(Category="Joining")
	void OpenJoinMenu();

	UFUNCTION(Category="Joining")
	void OpenMainMenu();

	UFUNCTION(Category="Joining")
	void JoinServer();

	IMenuInterface* MenuInterface;
};



