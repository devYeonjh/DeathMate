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
	for (FEnemySpawnData& SpawnData : EnemySpawnList)
	{
		if (CurrentAliveEnemyCount < MaxSpawnCount && SpawnData.EnemyClass)
		{
			SpawnEnemy(SpawnData.EnemyClass, 500.0f);
		}
	}
}

// Called every frame
void ADMEnemyFactory::Tick(float DeltaTime)
{
	/*Super::Tick(DeltaTime);

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
	}*/
	
}



void ADMEnemyFactory::SpawnEnemy(TSubclassOf<ADMEnemyActor> EnemyClassToSpawn, float MoveSpeed)
{
	if (EnemyClassToSpawn == nullptr || CurrentAliveEnemyCount >= MaxSpawnCount)
	{
		return;
	}
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	ADMEnemyActor* SpawnedEnemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClassToSpawn, SpawnLocation, SpawnRotation);
	if (SpawnedEnemy)
	{
		SpawnedEnemy->SetMoveSpeed(MoveSpeed);
		SpawnedEnemy->SetOwnerFactory(this);
		SpawnedEnemy->OnEnemyDieAction.AddLambda([this](int32 Value)->void
			{
				if (CurrentAliveEnemyCount <= 0)
					return;
				if (CurrentAliveEnemyCount-- == MaxSpawnCount)
					GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ADMEnemyFactory::HandleRespawn, RespawnCooldown, false);
			}
		);
		++CurrentAliveEnemyCount;
	}
	
	/*if (EnemyClassToSpawn == nullptr)
	{
		return;
	}
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	ADMEnemyActor* SpawndEnemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClassToSpawn, SpawnLocation, SpawnRotation);*/

}

void ADMEnemyFactory::NotifyEnemyDestroyed(TSubclassOf<ADMEnemyActor> DestroyedEnemyClass)
{
	CurrentAliveEnemyCount = FMath::Max(0, CurrentAliveEnemyCount - 1);

	if (DestroyedEnemyClass)	
	{
		FPendingRespawnData RespawnData;
		RespawnData.EnemyClass = DestroyedEnemyClass;

		PendingRespawnList.Add(RespawnData);

		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ADMEnemyFactory::HandleRespawn, RespawnCooldown, false);
	}
}

void ADMEnemyFactory::HandleRespawn()
{
	if (CurrentAliveEnemyCount >= MaxSpawnCount)
		return;

	// 리스트에서 하나 꺼냄
	FPendingRespawnData RespawnData = PendingRespawnList[0];
	PendingRespawnList.RemoveAt(0);

	SpawnEnemy(RespawnData.EnemyClass, 500.0f);

	// 다음 리스폰이 남아있으면 타이머 다시 설정
	if (PendingRespawnList.Num() > 0)
	{
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ADMEnemyFactory::HandleRespawn, RespawnCooldown, false);
	}
}

