// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlacTulip/Game/Interfaces/BlacTulipInteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

#include "BlacTulipNPCGoldenOwl.generated.h"


UCLASS()
class BLACTULIP_API ABlacTulipNPCGoldenOwl : public ACharacter, public IBlacTulipInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlacTulipNPCGoldenOwl();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	// Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
	class USphereComponent* CollisionSphere;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int OtherBodyIndex);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Widgets
	// Widgets/InteractionPrompt
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TSubclassOf<class UUserWidget> InteractionPromptWidgetClass;
	
	UPROPERTY()
	UUserWidget* InteractionPromptWidget;

	// Widgets/Dialogue	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	UPROPERTY()
	UUserWidget* DialogueWidget;

	// Widgets/Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	UWidgetComponent* NameWidget;

	// Interactions
	virtual void Interact(class ABlacTulipCharacter& Character) override;
	virtual void EndInteraction() override;
	virtual ABlacTulipCharacter* GetOverlappingCharacter() override;

	UPROPERTY()
	ABlacTulipCharacter* OverlappingCharacter;

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
