// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/ServerRow.h"
#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"


void UServerRow::Setup(class UMainMenu* InParent, uint32 InIndex)
{
    Parent = InParent;
    Index = InIndex;
    RowButton->OnClicked.AddDynamic(this,&UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
    Parent->SelectIndex(Index);
    uint32 TempValue = Parent->GetSelectedIndex();
    UE_LOG(LogTemp, Warning, TEXT("Clicked index: %d"), Index);
    UE_LOG(LogTemp, Warning, TEXT("Selected index: %d"), TempValue);
}
