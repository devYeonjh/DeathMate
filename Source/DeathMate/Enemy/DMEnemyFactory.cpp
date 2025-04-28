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

	if (CurrentTime > DelayTime)
	{
		CurrentTime = 0;

		if (EnemyClass.Num() >=2)
		{
			SpawnEnemy(EnemyClass[0], 500.0f);
			SpawnEnemy(EnemyClass[1], 1000.0f);
		}

		// ADMEnemyActor* Enemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClass[0], GetActorLocation(), GetActorRotation());
		// ADMEnemyActor* Enemy1 = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClass[1], GetActorLocation(), GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("Enemy is Spawned!"));
	}
	else
	{
		CurrentTime += DeltaTime;
	}
}

void ADMEnemyFactory::SpawnEnemy(TSubclassOf<ADMEnemyActor> EnemyClassToSpawn, float MoveSpeed)
{
	if (!EnemyClassToSpawn)
	{
		return;
	}
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	ADMEnemyActor* SpawndEnemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClassToSpawn, SpawnLocation, SpawnRotation);

	if (SpawndEnemy)
	{
		SpawndEnemy->SetMoveSpeed(MoveSpeed);
	}

}

