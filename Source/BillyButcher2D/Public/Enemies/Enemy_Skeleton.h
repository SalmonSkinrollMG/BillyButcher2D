﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Enemy_Skeleton.generated.h"

UCLASS()
class BILLYBUTCHER2D_API AEnemy_Skeleton : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Skeleton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
