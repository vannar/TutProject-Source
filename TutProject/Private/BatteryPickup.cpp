// Fill out your copyright notice in the Description page of Project Settings.

#include "TutProject.h"
#include "BatteryPickup.h"

ABatteryPickup::ABatteryPickup(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // the base power level of the battery
    PowerLevel = 150.f;
}

void ABatteryPickup::OnPickedUp_Implementation()
{
    // Call the parent Implementation of OnPickedUp first
    Super::OnPickedUp_Implementation();
    
    // destroy the battery
    Destroy();
    
    
}

