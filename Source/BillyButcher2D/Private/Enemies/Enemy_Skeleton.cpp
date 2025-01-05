// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy_Skeleton.h"


// Sets default values
AEnemy_Skeleton::AEnemy_Skeleton()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy_Skeleton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Skeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy_Skeleton::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

