// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMEnemyFactory.generated.h"

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
	float DelayTime = 1.5f;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ADMEnemyActor>> EnemyClass;

private:
	float CurrentTime = 0;

public:
	void SpawnEnemy(TSubclassOf<ADMEnemyActor> EnemyClassToSpawn, float MoveSpeed);

};
