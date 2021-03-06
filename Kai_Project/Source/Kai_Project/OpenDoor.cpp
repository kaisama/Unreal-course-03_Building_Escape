// Fill out your copyright notice in the Description page of Project Settings.

#include "Kai_Project.h"
#include "OpenDoor.h"


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

	// ...

	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find any PressurePlate (TriggerVolume) component in %s, please initialize it!!!"), *GetOwner()->GetName())
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (GetTotalMassOnPlate() >= TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate()
{
	if (PressurePlate == nullptr)
	{
		return 0;
	}

	TArray<AActor*> actors;

	PressurePlate->GetOverlappingActors(actors);

	float totalMass = 0;

	for (AActor *actor : actors) 
	{		
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return totalMass;
}

