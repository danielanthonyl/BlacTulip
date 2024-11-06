// Fill out your copyright notice in the Description page of Project Settings.


#include "BlacTulipWidgetPanelBase.h"

#include "Components/Button.h"

void UBlacTulipWidgetPanelBase::NativeConstruct()
{
	if(CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UBlacTulipWidgetPanelBase::OnclickCloseButton);
	}
}

void UBlacTulipWidgetPanelBase::OnclickCloseButton()
{
	RemoveFromParent();
	const FInputModeGameOnly InputModeGameOnly;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(InputModeGameOnly);
	PlayerController->bShowMouseCursor = false;
}
