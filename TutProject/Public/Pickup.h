// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class TUTPROJECT_API APickup : public AActor //TutProject_API
{
    GENERATED_BODY()
public:
	
    /** True when the pickup is able to be picked up, false if something deactivates the pickup. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
    bool bIsActive;
	
    /** Simple collision primitive to use as the root component. */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
    class USphereComponent* BaseCollisionComponent;
    //TSubobjectPtr<USphereComponent> BaseCollisionComponent;
    
    /** StaticMeshComponent to represent the pickup in the level. */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
    class UStaticMeshComponent* PickupMesh;
    //TSubobjectPtr<UStaticMeshComponent> PickupMesh;
    
    /** Function to call when Pickup is collected. */
    UFUNCTION(BlueprintNativeEvent)
    void OnPickedUp();
    
    APickup(const FObjectInitializer& ObjectInitializer);
};
