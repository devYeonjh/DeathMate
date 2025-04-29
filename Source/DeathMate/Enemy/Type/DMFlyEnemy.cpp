// Fill out your copyright notice in the Description page of Project Settings.


	#include "Enemy/Type/DMFlyEnemy.h"
    #include "GameFramework/Actor.h"
    #include "GameFramework/Character.h"
    #include "Kismet/GameplayStatics.h"
    #include "Engine/World.h"

	void ADMFlyEnemy::Move()
	{
		
		APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerCharacter == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Not Found"));
			return;
		}
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector EnemyLocation = GetActorLocation();

		FVector DirectionToPlayer = PlayerLocation - EnemyLocation;
		DirectionToPlayer.Z += 100.0f;
		DirectionToPlayer.Normalize();

		FVector Velocity = DirectionToPlayer * MoveSpeed * GetWorld()->GetDeltaSeconds();

		FVector NewLocation = EnemyLocation + Velocity;

		SetActorLocation(NewLocation);

	}
