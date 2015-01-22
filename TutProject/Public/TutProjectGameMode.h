// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SpawnVolume.h"
#include "TutProjectGameMode.generated.h"

// enum to store the current state of gameplay
enum class ETutProjectPlayState : short
{
    EPlaying,
    EGameOver,
    EUnknown
};

UCLASS(minimalapi)
class ATutProjectGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATutProjectGameMode(const FObjectInitializer& ObjectInitializer);
    
    virtual void Tick(float DeltaSeconds) OVERRIDE;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
    float DecayRate;
    
    ETutProjectPlayState GetCurrentState() const;
    void SetCurrentState(ETutProjectPlayState NewState);
    
    virtual void BeginPlay() OVERRIDE;
    
private:
    //TArrayBuilder<ASpawnVolume*> SpawnVolumeActors;
    TArray<ASpawnVolume*> SpawnVolumeActors;
    
    ETutProjectPlayState CurrentState;
    void HandleNewState(ETutProjectPlayState NewState);
    
};

FORCEINLINE ETutProjectPlayState ATutProjectGameMode::GetCurrentState() const
{
    return CurrentState;
}


