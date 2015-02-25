// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TutProject.h"
#include "TutProjectGameMode.h"
#include "TutProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TutProjectHud.h"

ATutProjectGameMode::ATutProjectGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    
    // set the default hud class
    HUDClass = ATutProjectHud::StaticClass();
    
    // base decay Rate
    DecayRate = 0.25f;
    
}

void ATutProjectGameMode::Tick(float DeltaSeconds)
{
    ATutProjectCharacter* MyCharacter = Cast<ATutProjectCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    if (MyCharacter != NULL)
    {
        // if the character still has power
        if (MyCharacter->PowerLevel > 0.05)
        {
            // decrease the characters power
            //MyCharacter->PowerLevel = FMath::FInterpTo(MyCharacter->PowerLevel, 0.f, DeltaSeconds, DecayRate);
        }
        else
        {
            SetCurrentState(ETutProjectPlayState::EGameOver);
        }
    }
    else
    {
        RestartGame();
        //ResetLevel();
    }
}

void ATutProjectGameMode::SetCurrentState(ETutProjectPlayState NewState)
{
    CurrentState = NewState;
    
    HandleNewState(NewState);
}

void ATutProjectGameMode::HandleNewState(ETutProjectPlayState NewState)
{
    switch (NewState)
    {
        // When we are plaing, the spawn volumes can spawn
        case ETutProjectPlayState::EPlaying:
            for (ASpawnVolume* Volume : SpawnVolumeActors)
            {
                Volume->EnableSpawning();
            }
            break;
        
        // if the game is over, the spawn volumes should deactivate
        case ETutProjectPlayState::EGameOver:
        {
            for (ASpawnVolume* Volume : SpawnVolumeActors)
            {
                Volume->DisableSpawning();
            }
            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            PlayerController->SetCinematicMode(true, true, true);
        }
            break;
        
        case ETutProjectPlayState::EUnknown:
        default:
            break;
    }
}

void ATutProjectGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    // find all spawn volume actors
    TArray<AActor*> FoundActors;
    
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
    
    for (auto Actor : FoundActors)
    {
        ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
        if (SpawnVolumeActor)
        {
            SpawnVolumeActors.Add(SpawnVolumeActor);
        }
    }
    
    SetCurrentState(ETutProjectPlayState::EPlaying);
}