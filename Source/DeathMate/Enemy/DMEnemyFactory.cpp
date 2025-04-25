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

		ADMEnemyActor* Enemy = GetWorld()->SpawnActor<ADMEnemyActor>(EnemyClass, GetActorLocation(), GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("Enemy is Spawned!"));
	}
	else
	{
		CurrentTime += DeltaTime;
	}
}

