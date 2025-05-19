// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMFlyEnemy.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ADMFlyEnemy::Move(float DeltaTime)
{
	// 플레이어 위치 가져오기
	APawn* PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Not Found"));
		return;
	}
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();

	// 거리 계산
	float DistanceToPlayer = FVector::Dist2D(PlayerLocation, EnemyLocation);

	// 감지 범위 내에 있는 경우에만 추적
	if (DistanceToPlayer <= DetectionRange)
	{
		FVector DirectionToPlayer = PlayerLocation - EnemyLocation;
		// DirectionToPlayer.Z += 50.f;
		DirectionToPlayer.Normalize();

		FVector Velocity = DirectionToPlayer * MoveSpeed * DeltaTime;

		FVector NewLocation = EnemyLocation + Velocity;

		SetActorLocation2D(NewLocation);
	}
	// 플레이어가 범위 밖에 있는 경우
	// 예: 대기 상태 또는 Idle 애니메이션 재생 등
}

	
