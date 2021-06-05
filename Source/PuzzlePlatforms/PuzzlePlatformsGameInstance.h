// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init();

	// Console Commands
	UFUNCTION(Exec, BlueprintCallable, Category="Console Commands")
	void LoadMenu();

	UFUNCTION(Exec, Category="Console Commands")
	void Host();

	UFUNCTION(Exec, Category="Console Commands")
	void Join(const FString& Address);

private:
	TSubclassOf<class UUserWidget> MenuClass;

};
