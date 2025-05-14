// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMEnemyFactory.generated.h"

class ADMEnemyActor;


UCLASS()
class DEATHMATE_API ADMEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADMEnemyActor> EnemyClass;

	UPROPERTY(EditAnywhere, Category="Enemy Spawn")
	int32 MaxSpawnCount = 3;

	UPROPERTY(EditAnywhere, Category="Enemy Spawn")
	float RespawnCooldown = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawn")
	float MoveSpeed = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawn")
	float AI = 0.f;
	

private:
	FTimerHandle RespawnTimerHandle;

	// 현재 살아있는 적 개수
	int32 CurrentAliveEnemyCount = 0;
	
	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void TryScheduleSpawn();

	UFUNCTION()
	void EnemyHandleDeath();
};
