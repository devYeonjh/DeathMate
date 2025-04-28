// Fill out your copyright notice in the Description page of Project Settings.


	#include "Enemy/Type/DMFlyEnemy.h"
    #include "GameFramework/Actor.h"
    #include "Kismet/GameplayStatics.h"
    #include "Engine/World.h"

	void ADMFlyEnemy::Move()
	{
		//// 날아다니는 몬스터의 이동 방식 처리
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation2 = CurrentLocation + FVector(0.0f, 0.0f, 1.0f); // Z축을 따라 상승
		SetActorLocation(NewLocation2); // 비행 시, 직접 위치 변경

		//FVector CurrentLocation = GetActorLocation();
		//AActor* PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		//if (PlayerActor)
		//{
		//	FVector PlayerLocation = PlayerActor->GetActorLocation(); // 플레이어 위치 가져오기

		//	FVector DirectionToPlayer = PlayerLocation - CurrentLocation; // 플레이어와 몬스터 간의 백터 차이 계산(방향 백터)

		//	DirectionToPlayer.Normalize();

		//	FVector NewLocation = CurrentLocation + (DirectionToPlayer * MoveSpeed * GetWorld()->DeltaTimeSeconds); // 이동할 위치 계산

		//	SetActorLocation(NewLocation); // 몬스터의 위치를 계산된 위치로 이동
		//}
		//else
		//{
		//	// 플레이어가 없으면 그냥 상승 (기존 동작 유지)
		//	FVector NewLocation2 = CurrentLocation + FVector(0.0f, 0.0f, 1.0f);  // Z축을 따라 상승
		//	SetActorLocation(NewLocation2); // 비행 시, 직접 위치 변경
		//}


	}
