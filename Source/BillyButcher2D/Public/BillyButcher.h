// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "Enemies/CharacterBase.h"
#include "BillyButcher.generated.h"

/**
 * 
 */
UCLASS()
class BILLYBUTCHER2D_API ABillyButcher : public ACharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// Movement input function
	void Move(const FInputActionValue& Value);

	// Jump to input function
	virtual void Jump() override;
	void RotateController() const;

	// Enhanced Input System
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


private:
	/*
	 * //Always move on X Axis , this constant will come in handy when flipping the player based on direcition. Y axis is taken care by jump.
	 */
	const FVector MovementDirection{FVector(1.0 , 0.0 ,0.0)}; 
	
};
