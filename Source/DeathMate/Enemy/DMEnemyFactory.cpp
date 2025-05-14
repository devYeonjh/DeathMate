// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMEnemyFactory.h"
#include "DMEnemyActor.h"


// Sets default values
ADMEnemyFactory::ADMEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADMEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	// 초기 적 소환(MaxSpawnCount 만큼)
	//if (CurrentAliveEnemyCount < MaxSpawnCount)
	//{
	//	SpawnEnemy();
	//}

	TryScheduleSpawn();
}



void ADMEnemyFactory::SpawnEnemy()
{
	if (CurrentAliveEnemyCount >= MaxSpawnCount )
	{
		return;
	}

	ADMEnemyActor* SpawnedEnemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClass, GetActorLocation(), GetActorRotation());
	if (SpawnedEnemy)
	{
		++CurrentAliveEnemyCount;
		UE_LOG(LogTemp, Warning, TEXT("CurrentAliveEnemyCount: %d"), CurrentAliveEnemyCount);
		SpawnedEnemy->SetOwnerFactory(this);
		SpawnedEnemy->OnEnemyDieAction.AddLambda([this]()->void
			{
				CurrentAliveEnemyCount = FMath::Max(0, CurrentAliveEnemyCount - 1);
				UE_LOG(LogTemp, Warning, TEXT("CurrentAliveEnemyCount: %d"), CurrentAliveEnemyCount);
				TryScheduleSpawn();
			}
		);
	}
	// 적이 소환된 후 RespawnCooldown 시간 후에 다시 소환 시도
	if (CurrentAliveEnemyCount < MaxSpawnCount)
	{
		TryScheduleSpawn();
	}
}

void ADMEnemyFactory::TryScheduleSpawn()
{
	if (CurrentAliveEnemyCount >= MaxSpawnCount) return;

	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&ADMEnemyFactory::SpawnEnemy,
		RespawnCooldown,
		false
	);

}

