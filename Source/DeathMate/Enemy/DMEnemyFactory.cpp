// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMEnemyFactory.h"
#include "Enemy/Type/DMFlyEnemy.h"
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

	for (int i = 0; i < MaxSpawnCount; i++)
	{
		ADMEnemyActor* SpawnedEnemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClass, GetActorLocation() + (SpawnOffset * i), GetActorRotation());
		if (SpawnedEnemy)
		{
			++CurrentAliveEnemyCount;
			SettingEnemy(SpawnedEnemy);
		}
	}

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
		SettingEnemy(SpawnedEnemy);
	}

	if (RespawnCooldown > 0) //리스폰 쿨타임이 있는경우에만 추가 생성시도 없는경우 영원히 리스폰되지않음
	{
		//  다시 생성 시도
		TryScheduleSpawn();
	}
}

void ADMEnemyFactory::TryScheduleSpawn()
{
	// 최대 스폰 카운트 이상이면 생성하지않음
	if (CurrentAliveEnemyCount >= MaxSpawnCount) return;

	//RespawnCooldown 이후에 SpawnEnemy를 통해 Enemy생성
	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&ADMEnemyFactory::SpawnEnemy,
		RespawnCooldown,
		false
	);

}

void ADMEnemyFactory::EnemyHandleDeath()
{
	bool bIsFull = CurrentAliveEnemyCount == MaxSpawnCount;
	CurrentAliveEnemyCount = FMath::Max(0, CurrentAliveEnemyCount - 1);

	if (bIsFull)
		TryScheduleSpawn();
}

void ADMEnemyFactory::SettingEnemy(ADMEnemyActor* SpawnedEnemy)
{
	SpawnedEnemy->SetMoveSpeed(MoveSpeed);
	SpawnedEnemy->OnEnemyDieAction.AddUObject(this, &ADMEnemyFactory::EnemyHandleDeath);
}

