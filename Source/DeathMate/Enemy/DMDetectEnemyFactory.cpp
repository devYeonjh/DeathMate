// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMDetectEnemyFactory.h"
#include "Enemy/Type/DMFlyEnemy.h"

void ADMDetectEnemyFactory::SettingEnemy(ADMEnemyActor* SpawnedEnemy)
{
	Super::SettingEnemy(SpawnedEnemy);

	ADMFlyEnemy* SpawnedFly = Cast<ADMFlyEnemy>(SpawnedEnemy);
	if (SpawnedFly)
	{
		SpawnedFly->DetectionRange = DetectionRange;
	}
}
