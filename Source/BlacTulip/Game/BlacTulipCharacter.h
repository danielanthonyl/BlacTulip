// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/BlacTulipInteractionInterface.h"

#include "BlacTulipCharacter.generated.h"

UCLASS()
class BLACTULIP_API ABlacTulipCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlacTulipCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* ThirdPersonCameraCameraComponent;

	// Inputs
	// Inputs/Movements
	void MoveControl(const FInputActionValue& Value);
	void LookControl(const FInputActionValue& Value);
	void SprintControl(const FInputActionInstance& Instance);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputLook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputJump;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputSprint;

	//Inputs/interactions
	void InteractStartControl(const FInputActionValue & Value);
	void InteractEndControl(const FInputActionValue & Value);
	void SetInteractiveNPC(IBlacTulipInteractionInterface* NPC);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* InputInteract;

	IBlacTulipInteractionInterface* InteractiveNPC;

	bool bInteractActionPressed = false;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
