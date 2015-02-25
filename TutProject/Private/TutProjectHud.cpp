// Fill out your copyright notice in the Description page of Project Settings.

#include "TutProject.h"
#include "TutProjectHud.h"
#include "TutProjectGameMode.h"
#include "TutProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"


ATutProjectHud::ATutProjectHud(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // use the RobotoDistanceField font from the engine
    static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
    HUDFont  = HUDFontOb.Object;
    
    
}

void ATutProjectHud::DrawHUD()
{
    
    // Get the screen dimensions
    FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
    
    // Call to the parent version of DrawHUD
    Super::DrawHUD();
    
    // Get the character adn print it's power level
    ATutProjectCharacter* MyCharacter = Cast<ATutProjectCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (MyCharacter != NULL)
    {
        FString PowerLevelString = FString::Printf(TEXT("%10.1f"), FMath::Abs(MyCharacter->PowerLevel));
        DrawText(PowerLevelString, FColor::White, 50, 50, HUDFont);
    }
    
    ATutProjectGameMode* MyGameMode = Cast<ATutProjectGameMode>(UGameplayStatics::GetGameMode(this));
    
    // if the game is over
    if (MyGameMode->GetCurrentState() == ETutProjectPlayState::EGameOver)
    {
        // create a variable for storing the size of printing game over
        FVector2D GameOverSize;
        GetTextSize(TEXT("GAME OVER"), GameOverSize.X, GameOverSize.Y, HUDFont);
        DrawText(TEXT("GAME OVER"),FColor::White, (ScreenDimensions.X - GameOverSize.X)/2.0f,(ScreenDimensions.Y - GameOverSize.Y)/2.0f, HUDFont);
    }
}