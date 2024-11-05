// Fill out your copyright notice in the Description page of Project Settings.

#include "BlacTulipNPCGoldenOwl.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

#include "BlacTulip/Game/BlacTulipCharacter.h"

// Sets default values
ABlacTulipNPCGoldenOwl::ABlacTulipNPCGoldenOwl()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(300.0f);

}

// Called when the game starts or when spawned
void ABlacTulipNPCGoldenOwl::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlacTulipNPCGoldenOwl::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ABlacTulipNPCGoldenOwl::OnOverlapEnd);
}

void ABlacTulipNPCGoldenOwl::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedComponent && OtherActor)
	{
		if (OtherActor->IsA(ABlacTulipCharacter::StaticClass()))
		{
			if (InteractionPromptWidgetClass)
			{
				if (!InteractionPromptWidget->IsValidLowLevel())
				{
					InteractionPromptWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionPromptWidgetClass);
				}
                
				if (InteractionPromptWidget)
				{
					if(!InteractionPromptWidget->IsInViewport())
					{
						InteractionPromptWidget->AddToViewport();
					}
				}
			}
		}
	}
}

void ABlacTulipNPCGoldenOwl::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int OtherBodyIndex)
{
	if (OverlappedComponent && OtherActor)
	{
		if (OtherActor->IsA(ABlacTulipCharacter::StaticClass()))
		{
			if (InteractionPromptWidgetClass)
			{
				if (InteractionPromptWidget)
				{
					if (InteractionPromptWidget->IsValidLowLevel() && InteractionPromptWidget->IsInViewport())
					{
						InteractionPromptWidget->RemoveFromParent();	
					}
				}
			}
		}
	}
}

// Called every frame
void ABlacTulipNPCGoldenOwl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABlacTulipNPCGoldenOwl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

}

