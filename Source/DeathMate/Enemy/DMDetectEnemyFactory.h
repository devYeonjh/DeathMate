// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/DMEnemyFactory.h"
#include "DMDetectEnemyFactory.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMDetectEnemyFactory : public ADMEnemyFactory
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Enemy Spawn")
	float DetectionRange = 0.f;

protected:
	virtual void SettingEnemy(ADMEnemyActor* SpawnedEnemy) override;
	
};
