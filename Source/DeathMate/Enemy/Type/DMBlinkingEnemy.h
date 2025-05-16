// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/DMEnemyActor.h"
#include "DMBlinkingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMBlinkingEnemy : public ADMEnemyActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime) override;
	void UpdateVisibility(float DeltaTime);

private:
	float MoveDistance = 800.f; // 최대 이동 거리
	FVector MoveDirection = FVector(1, 0, 0); // 기본 X축 방향
	FVector Direction = FVector::ZeroVector; // 이동 방향 기본값 0, 0, 0
	FVector StartLocation;
	bool bMovingForward = true;

	UMaterialInstanceDynamic* DynMaterial = nullptr;

	float ToggleInterval = 1.5f;
	float TimeSinceLastToggle = 0.f;
	bool bVisible = true;
};

