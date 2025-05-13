// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMEnemyFactory.h"
#include "DMEnemyActor.h"


// Sets default values
ADMEnemyFactory::ADMEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADMEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADMEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (FEnemySpawnData& SpawnData : EnemySpawnList)
	{
		SpawnData.CurrentTime += DeltaTime;

		if (SpawnData.CurrentTime >= SpawnData.DelayTime)
		{
			SpawnData.CurrentTime = 0.f;

			if (SpawnData.EnemyClass != nullptr)
			{
				float MoveSpeed = (SpawnData.DelayTime < 2.f) ? 1000.f : 500.f;
				SpawnEnemy(SpawnData.EnemyClass, MoveSpeed);
			}
		}
	}
	
}

void ADMEnemyFactory::SpawnEnemy(TSubclassOf<ADMEnemyActor> EnemyClassToSpawn, float MoveSpeed)
{
	if (EnemyClassToSpawn == nullptr)
	{
		return;
	}
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	ADMEnemyActor* SpawndEnemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClassToSpawn, SpawnLocation, SpawnRotation);

	/*if (SpawndEnemy)
	{
		SpawndEnemy->SetMoveSpeed(MoveSpeed);

	};*/

}

