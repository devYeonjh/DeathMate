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
	virtual void Move(float DeltaTime) override;
	virtual void BeginPlay() override;
	
public:
	// 감지 범위 설정
	UPROPERTY(EditAnywhere, Category="AI")
	float DetectionRange = 1000.f;

private:
	UFUNCTION()
	void ResetPosition(const FVector& pos);

	FVector StartLocation;
	FRotator StartRotation;
};
