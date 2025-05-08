// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMEnemyFactory.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADMEnemyActor> EnemyClass;

	UPROPERTY(EditAnywhere)
	float DelayTime = 1.5f;

	UPROPERTY(EditAnywhere)
	float MoveDistance = 800.0f;

	float CurrentTime = 0.0f;


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


public:
	void SpawnEnemy(TSubclassOf<ADMEnemyActor> EnemyClassToSpawn, float MoveSpeed);

};
