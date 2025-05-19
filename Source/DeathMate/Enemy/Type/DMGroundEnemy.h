// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/DMEnemyActor.h"
#include "DMGroundEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMGroundEnemy : public ADMEnemyActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime) override;

private:
	FVector Direction = FVector::ZeroVector; // 이동 방향 기본값 0, 0, 0
	bool bMovingForward = true;

	bool bCanMove = false;
	FTimerHandle MovementEnableTimerHandle;
	
};
