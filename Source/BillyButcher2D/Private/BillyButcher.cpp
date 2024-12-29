// Fill out your copyright notice in the Description page of Project Settings.


#include "BillyButcher.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABillyButcher::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ABillyButcher::RotateController() const
{
	if (Controller && GetCharacterMovement())
	{
		const float MovementX = GetCharacterMovement()->GetCurrentAcceleration().X;
		if (MovementX < 0)
		{
			Controller->SetControlRotation(FRotator(0, 180.0f, 0));
		}
		if(MovementX > 0)
		{
			Controller->SetControlRotation(FRotator(0, 0, 0));
		}
	}
}

void ABillyButcher::Move(const FInputActionValue& Value)
{
	
	float Movement = Value.Get<float>();
	RotateController();
	AddMovementInput(MovementDirection, Movement);
}

void ABillyButcher::Jump()
{
	Super::Jump();
}

void ABillyButcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABillyButcher::Move);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABillyButcher::Jump);

	}
}


