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
	virtual void Move() override;

private:
	float MoveDistance = 800.0f; // 최대 이동 거리
	FVector MoveDirection = FVector(1, 0, 0); // 기본 X축 방향

	FVector Direction = FVector::ZeroVector; // 이동 방향 기본값 0, 0, 0
	FVector StartLocation;
	bool bMovingForward = true;
	
};
