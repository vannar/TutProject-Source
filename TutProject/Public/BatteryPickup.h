// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class TUTPROJECT_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
public:
    /** Sets the amount of power the battery gives to the player */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
    float PowerLevel;
	
    /** Override the OnPickUp function (use Implementation because this is a BlueprintNativeEvent)*/
    void OnPickedUp_Implementation() OVERRIDE;
    
    ABatteryPickup(const FObjectInitializer& ObjectInitializer);
	
};
