// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BillyButcher.generated.h"

/**
 * 
 */
UCLASS()
class BILLYBUTCHER2D_API ABillyButcher : public APaperCharacter
{
	GENERATED_BODY()


	// Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	// Movement Input Handlers
	void Move(const FInputActionValue& Value);
	
};
