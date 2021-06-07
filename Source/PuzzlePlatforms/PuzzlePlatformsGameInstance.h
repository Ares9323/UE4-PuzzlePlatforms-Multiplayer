// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init();

	// Console Commands
	UFUNCTION(Exec, BlueprintCallable, Category="Console Commands")
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable, Category="Console Commands")
	void LoadInGameMenu();

	UFUNCTION(Exec, Category="Console Commands")
	void Host() override;

	UFUNCTION(Exec, Category="Console Commands")
	void Join(const FString& Address) override;

	UFUNCTION(Exec, Category="Console Commands")
	void JoinList(const FString& Address) override;

	UFUNCTION(Exec, Category="Console Commands")
	virtual void LoadMainMenu() override;

	UFUNCTION(Exec, Category="Console Commands")
	virtual void RefreshServerList() override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);

	void CreateSession();

};
