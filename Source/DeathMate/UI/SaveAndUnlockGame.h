// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveAndUnlockGame.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API USaveAndUnlockGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere) 
	int32 HighestUnlockedStage;
};
