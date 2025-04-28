// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/DMEnemyActor.h"
#include "DMFlyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMFlyEnemy : public ADMEnemyActor
{
	GENERATED_BODY()

protected:
	virtual void Move() override;
	
};
