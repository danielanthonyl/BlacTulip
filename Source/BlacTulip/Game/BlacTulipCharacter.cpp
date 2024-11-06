// Fill out your copyright notice in the Description page of Project Settings.


#include "BlacTulipCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABlacTulipCharacter::ABlacTulipCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->SetupAttachment(RootComponent);

	ThirdPersonCameraCameraComponent = CreateDefaultSubobject<UCameraComponent>("Third Person Camera");
	ThirdPersonCameraCameraComponent->SetupAttachment(SpringArmComponent);
	ThirdPersonCameraCameraComponent->Activate(true);
	

	SpringArmComponent->bUsePawnControlRotation = true;
	ThirdPersonCameraCameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ABlacTulipCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 1);
		}
	}
}

// Called every frame
void ABlacTulipCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



// Called to bind functionality to input
void ABlacTulipCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this,&ABlacTulipCharacter::MoveControl);
			EnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this,&ABlacTulipCharacter::LookControl);
			EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Triggered, this, &ABlacTulipCharacter::Jump);
			EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Triggered, this, &ABlacTulipCharacter::InteractStartControl);
			EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Completed, this, &ABlacTulipCharacter::InteractEndControl);
			
			EnhancedInputComponent->BindAction(InputSprint, ETriggerEvent::Triggered, this, &ABlacTulipCharacter::SprintControl);
			EnhancedInputComponent->BindAction(InputSprint, ETriggerEvent::Completed, this, &ABlacTulipCharacter::SprintControl);
			EnhancedInputComponent->BindAction(InputSprint, ETriggerEvent::Canceled, this, &ABlacTulipCharacter::SprintControl);
			
		}
	}
}

void ABlacTulipCharacter::MoveControl(const FInputActionValue& Value)
{
	const FVector2d MovementInput = Value.Get<FVector2d>();

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementInput.Y);
	AddMovementInput(RightDirection, MovementInput.X);
}

void ABlacTulipCharacter::LookControl(const FInputActionValue& Value)
{
	const FVector2D Direction = Value.Get<FVector2D>();

	AddControllerPitchInput(Direction.Y);
	AddControllerYawInput(Direction.X);
}


void ABlacTulipCharacter::SprintControl(const FInputActionInstance& Instance)
{
	if (const ETriggerEvent TriggeredEvent = Instance.GetTriggerEvent(); TriggeredEvent == ETriggerEvent::Triggered)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
	else if (TriggeredEvent == ETriggerEvent::Completed || TriggeredEvent == ETriggerEvent::Canceled)
	{
		GetCharacterMovement()->MaxWalkSpeed = 500;
	} 
}

void ABlacTulipCharacter::InteractStartControl(const FInputActionValue& Value)
{
	if(InteractiveNPC != nullptr)
	{
		if(InteractiveNPC->GetOverlappingCharacter() == this)
		{
			InteractiveNPC->Interact(*this);

			const FInputModeUIOnly InputModeUIOnly;
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			PlayerController->SetInputMode(InputModeUIOnly);
			PlayerController->bShowMouseCursor = true;
		} else
		{
			
		UE_LOG(LogTemp, Warning, TEXT("character not overlaping npc"))
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("not interactive npc"))
	}
}

void ABlacTulipCharacter::InteractEndControl(const FInputActionValue& Value)
{
}

void ABlacTulipCharacter::SetInteractiveNPC(IBlacTulipInteractionInterface* NPC)
{
	InteractiveNPC = NPC;
}




