// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class TUTPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
    
public:
    ASpawnVolume(const FObjectInitializer& ObjectInitializer);
    
    /** BoxComponent to specify the spawning area within the level */
    UPROPERTY(VisibleInstanceOnly, Category = Spawning)
    class UBoxComponent* WhereToSpawn;
    
    /** The Pickup to Spawn */
    UPROPERTY(EditAnywhere, Category = Spawning)
    TSubclassOf<class APickup> WhatToSpawn;
    //class APickup WhatToSpawn;
    
    /** Minimun spawn delay */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
    float SpawnDelayRangeLow;
    
    /** Maximun spawn delay */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
    float SpawnDelayRangeHigh;
    
    /** Finds a random point within the BoxComponent */
    UFUNCTION(BlueprintPure, Category = Spawning)
    FVector GetRandomPointInVolume();
    
    virtual void Tick(float DeltaSeconds) OVERRIDE;
    
    void EnableSpawning();
    
    void DisableSpawning();
    
    
private:
    /** Whelther or not Spawning is enabled*/
    bool bSpawningEnabled;
    
    /** Calculates a random spawn delay */
    float GetRandomSpawnDelay();
    
    /** The current spawn delay */
    float SpawnDelay;
    
    /** Handles the spawning of a new pickup */
    void SpawnPickup();
    
    /** the timer for  when to spawn the pickup */
    float SpawnTime;
	
};
