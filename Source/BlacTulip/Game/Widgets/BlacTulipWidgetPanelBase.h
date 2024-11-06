// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlacTulipWidgetPanelBase.generated.h"

/**
 * 
 */
UCLASS()
class BLACTULIP_API UBlacTulipWidgetPanelBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Title")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Close", meta = (BindWidget))
	class UButton* CloseButton;
	
	UFUNCTION()
	void OnclickCloseButton();

protected:
	virtual void NativeConstruct() override;
	
};
