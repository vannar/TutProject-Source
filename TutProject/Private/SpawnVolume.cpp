// Fill out your copyright notice in the Description page of Project Settings.

#include "TutProject.h"
#include "SpawnVolume.h"
#include "Pickup.h"

ASpawnVolume::ASpawnVolume(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Create the simple StaticMeshComponent to represent the pickup in the level
    WhereToSpawn = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));
    
    // set the StaticMeshComponent as the root component
    RootComponent = WhereToSpawn;
    
    // set the spawn delay ranhe and get the first spawndelay
    SpawnDelayRangeLow = 1.0f;
    SpawnDelayRangeHigh = 4.5f;
    SpawnDelay = GetRandomSpawnDelay();
    
    // make  the SpawnVolume Tickable
    PrimaryActorTick.bCanEverTick = true;
    
}

void ASpawnVolume::SpawnPickup()
{
    // If we have set something to spawn
    if(WhatToSpawn != NULL)
    {
        // Check for a valid world
        UWorld* const World = GetWorld();
        if (World)
        {
            // set spawn parameters
            FActorSpawnParameters SpawnParems;
            SpawnParems.Owner = this;
            SpawnParems.Instigator = Instigator;
            
            // get random location to spawn at
            FVector SpawnLocation = GetRandomPointInVolume();
            
            // get a random rotation for the spawned item
            FRotator SpawnRotator;
            SpawnRotator.Yaw = FMath::FRand() * 360.f;
            SpawnRotator.Pitch = FMath::FRand() * 360.f;
            SpawnRotator.Roll = FMath::FRand() * 360.f;
            
            // spawn pickup
            APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotator, SpawnParems);
        }
    }
}

float ASpawnVolume::GetRandomSpawnDelay()
{
    // get a random float that falls within the spawn delay range
    return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    FVector RandomLocation;
    float MinX, MinY, MinZ;
    float MaxX, MaxY, MaxZ;
    
    FVector Origin;
    FVector BoxExtent;
    
    // get the SpawnVolumes origin and box extent
    Origin = WhereToSpawn->Bounds.Origin;
    BoxExtent = WhereToSpawn->Bounds.BoxExtent;
    
    //calulate the minimun x, y, and z
    MinX = Origin.X - BoxExtent.X / 2.f;
    MinY = Origin.Y - BoxExtent.Y / 2.f;
    MinZ = Origin.Z - BoxExtent.Z / 2.f;
    
    //calulate the maximun x, y, and z
    MaxX = Origin.X + BoxExtent.X / 2.f;
    MaxY = Origin.Y + BoxExtent.Y / 2.f;
    MaxZ = Origin.Z + BoxExtent.Z / 2.f;
    
    // the random spawn location will fall between the min and max x,y,z
    RandomLocation.X = FMath::FRandRange(MinX, MaxX);
    RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
    RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);
    
    // return the random spawn location
    return RandomLocation;
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
    // if spawning is not enabled do nothing
    if (!bSpawningEnabled)
        return;
    
    // allows add deltaSeconds to our spawn Time
    SpawnTime += DeltaSeconds;
    
    bool bShouldSpawn = (SpawnTime > SpawnDelay);
    
    if (bShouldSpawn)
    {
        SpawnPickup();
        
        // deduct spawn delay from accumulated time value
        SpawnTime -= SpawnDelay;
        
        SpawnDelay = GetRandomSpawnDelay();
    }
}

void ASpawnVolume::EnableSpawning()
{
    bSpawningEnabled = true;
}

void ASpawnVolume::DisableSpawning()
{
    bSpawningEnabled = false;
}

