// Fill out your copyright notice in the Description page of Project Settings.

#include "TutProject.h"
#include "Pickup.h"

APickup :: APickup(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // The pickup is valid when it is created
    bIsActive = true;
    
    // Create the root SphereComponent to handle the pickup's collision
    BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));
    
    // Set the SphereComponent as the root component
    RootComponent = BaseCollisionComponent;
    
    // Creat the StaticMeshComponent
    PickupMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));
    
    // turn physics on for the static mesh
    PickupMesh->SetSimulatePhysics(true);
    
    // attach the static mesh component to the root component
    PickupMesh->AttachTo(RootComponent);
}

void APickup::OnPickedUp_Implementation()
{
    // There is no default behaviour for a Pickup when it is picked up
}
