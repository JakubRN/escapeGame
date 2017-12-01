// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGame.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!Owner) {
		UE_LOG(LogTemp, Error, TEXT("Owner not set"));
	}

}

void UOpenDoor::OpenDoor()
{
	if (!Owner) return;
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.f));

}

void UOpenDoor::CloseDoor()
{
	if (!Owner) return;
	Owner->SetActorRotation(FRotator(0.0f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );


	if (GetTotalMassOfActorsOnPlate() > 40.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	// ...

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}

	
}
float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;	
	if (!PressurePlate) return TotalMass;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* Actor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("%s on a pressure plate!"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
