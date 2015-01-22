// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TutProjectHud.generated.h"

/**
 * 
 */
UCLASS()
class TUTPROJECT_API ATutProjectHud : public AHUD
{
	GENERATED_BODY()
    
public:
    /** Variable for store the font */
    UPROPERTY()
    UFont* HUDFont;
    
    /** Primary draw call for HUD */
    virtual void DrawHUD() OVERRIDE;
	
    ATutProjectHud(const FObjectInitializer& ObjectInitializer);
};
