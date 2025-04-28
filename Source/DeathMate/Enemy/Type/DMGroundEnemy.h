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
	float MoveDistance = 500.0f;
	FVector MoveDirection = FVector(1, 0, 0); // �⺻ X�� ����

	FVector Direction = FVector::ZeroVector; // �̵� ���� �⺻�� 0, 0, 0
	FVector StartLocation;
	bool bMovingForward = true;
	
};
