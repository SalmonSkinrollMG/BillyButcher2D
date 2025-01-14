// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TraceStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStartPosition"));
	TraceEndPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEndPosition"));
	PrimaryActorTick.bCanEverTick = true;
	CharacterMovementComponent = nullptr;
	TraceStartPosition->SetupAttachment(RootComponent);
	TraceEndPosition->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(!CharacterMovementComponent)
	{
		CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	}
	ConstrainMovementOnYAxis();
}

void ACharacterBase::ConstrainMovementOnYAxis() const
{
	CharacterMovementComponent->bConstrainToPlane = true;
	CharacterMovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

AActor* ACharacterBase::TraceAttack()
{
	AActor* HitActor{nullptr};
    FVector Start = TraceStartPosition->GetComponentLocation();
    FVector End = TraceEndPosition->GetComponentLocation();
	
    FCollisionObjectQueryParams ObjectQueryParams;
    ObjectQueryParams.AddObjectTypesToQuery(UEngineTypes::ConvertToCollisionChannel(CollisionObjectType));

    // Setup query parameters
    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = false;
    QueryParams.AddIgnoredActor(this);
	
    FHitResult OutHit;

    // Perform the box trace
    bool bHit = GetWorld()->SweepSingleByObjectType(
        OutHit,                    
        Start,
        End,
        TraceRotation.Quaternion(),
        ObjectQueryParams,
        FCollisionShape::MakeBox(TraceExtend),
        QueryParams
    );

	HitActor = OutHit.GetActor();

	if(bDrawDebug)
	{
	    FColor TraceColor =FColor::Green;
	    DrawDebugBox(GetWorld(), Start, TraceExtend, TraceRotation.Quaternion(), TraceColor, false, 1.0f);
	    DrawDebugBox(GetWorld(), End, TraceExtend, TraceRotation.Quaternion(), TraceColor, false, 1.0f);
	    DrawDebugLine(GetWorld(), Start, End, TraceColor, false, 1.0f);
		if (bHit)
		{
			TraceColor = FColor::Red;
			DrawDebugBox(GetWorld(), OutHit.Location, TraceExtend, TraceRotation.Quaternion(), TraceColor, false, 1.0f);
			UE_LOG(LogTemp, Warning, TEXT("TraceAttack: Hit Actor: %s"), *OutHit.GetActor()->GetName());
		}
	}
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TraceAttack: No hit detected."));
    }
	return HitActor;
}

AActor* ACharacterBase::TraceExplosion()
{
	AActor* HitActor = nullptr;

	// Get the actor's center as the starting point
	FVector Center = GetActorLocation();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(UEngineTypes::ConvertToCollisionChannel(CollisionObjectType));

	// Setup query parameters
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.AddIgnoredActor(this);

	FHitResult OutHit;

	// Perform the radial sphere trace
	bool bHit = GetWorld()->SweepSingleByObjectType(
		OutHit,
		Center,
		Center,
		FQuat::Identity, 
		ObjectQueryParams,
		FCollisionShape::MakeSphere(ExplosionRadius),
		QueryParams
	);


	if (bHit)
	{
		HitActor = OutHit.GetActor();
		if (HitActor)
		{
			if (bDrawDebug)
			{
				FColor HitColor = FColor::Red;
				DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 10.0f, 12, HitColor, false, 1.0f);
			}
			UE_LOG(LogTemp, Warning, TEXT("TraceExplosion: Hit Actor: %s"), *HitActor->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TraceExplosion: No actors hit in the explosion radius."));
	}
	
	if (bDrawDebug)
	{
		FColor TraceColor = bHit ? FColor::Red : FColor::Green;
		DrawDebugSphere(GetWorld(), Center, ExplosionRadius, 24, TraceColor, false, 1.0f);
	}

	return HitActor;
}



