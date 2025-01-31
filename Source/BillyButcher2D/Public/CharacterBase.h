﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CharacterBase.generated.h"

UCLASS()
class BILLYBUTCHER2D_API ACharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(EditAnywhere)
	USceneComponent* TraceStartPosition;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* TraceEndPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ConstrainMovementOnYAxis() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable , Category="CharacterFunctions")
	AActor* TraceAttack();
	
	UFUNCTION(BlueprintCallable , Category="CharacterFunctions")
	AActor* TraceExplosion();


	UPROPERTY(BlueprintReadWrite ,EditAnywhere, Category="AttackTraceVariable")
	TEnumAsByte<EObjectTypeQuery> CollisionObjectType{};

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="AttackTraceVariable")
	FVector TraceExtend{FVector::ZeroVector};

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="AttackTraceVariable")
	FRotator TraceRotation{FRotator::ZeroRotator};

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="AttackTraceVariable")
	float ExplosionRadius{5.0f};

	UPROPERTY(BlueprintReadWrite , EditAnywhere, Category="Debug")
	bool bDrawDebug{false};
};
