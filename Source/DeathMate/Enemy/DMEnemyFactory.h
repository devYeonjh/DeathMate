// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMEnemyFactory.generated.h"

class ADMEnemyActor;

USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADMEnemyActor> EnemyClass;

	UPROPERTY(EditAnywhere)
	float DelayTime = 1.5f;

	float CurrentTime = 0.f;

};

USTRUCT()
struct FPendingRespawnData
{
	GENERATED_BODY()

	UPROPERTY()

	TSubclassOf<ADMEnemyActor> EnemyClass;
};

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	TArray<FEnemySpawnData> EnemySpawnList;

	UPROPERTY(EditAnywhere, Category="Enemy Spawn")
	int32 MaxSpawnCount = 3;

	UPROPERTY(EditAnywhere, Category="Enemy Spawn")
	float RespawnCooldown = 3.0f;

	// 현재 살아있는 적 개수
	int32 CurrentAliveEnemyCount = 0;

	void SpawnEnemy(TSubclassOf<ADMEnemyActor> EnemyClassToSpawn, float MoveSpeed);
	void NotifyEnemyDestroyed(TSubclassOf<ADMEnemyActor> DestroyedEnemyClass);
	void HandleRespawn();

private:
	TArray<FPendingRespawnData> PendingRespawnList;
	FTimerHandle RespawnTimerHandle;
	
};
