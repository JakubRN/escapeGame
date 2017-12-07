// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	float Reach = 130.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;


	//grab what's in reach
	void Grab();
	void Release();
	void FindPhysicsHandleComponent();
	void SetupInputComponent();

	const FHitResult GetFirstPhysicsBodyInReach();
	FVector GetLineTraceStart();
	FVector GetLineTraceEnd();


	FVector TranslationVector;
	float HitDistance = 0.f;
	FVector TargetInitialPosition;
	FRotator TargetInitialRotation;
	
	FVector PlayerInitialPosition;
	FRotator PlayerInitialRotation;
	
	FVector PlayerPosition;
	FRotator PlayerRotation;
};
