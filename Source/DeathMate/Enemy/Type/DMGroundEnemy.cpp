// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMGroundEnemy.h"

void ADMGroundEnemy::Move()
{
	FVector CurrentLocation = GetActorLocation();

	float TraveledDistance = FVector::Dist(StartLocation, CurrentLocation);

	if (TraveledDistance >= MoveDistance)
	{
		bMovingForward = !bMovingForward;
		StartLocation = CurrentLocation; // 기준 위치 갱신
	}
	if (bMovingForward)
	{
		Direction = MoveDirection; // 앞으로 이동
	}
	else
	{
		Direction = -MoveDirection; // 뒤로 이동
	}
	FVector NewLocation = CurrentLocation + (Direction * MoveSpeed * CurrentDeltaTime);
	SetActorLocation(NewLocation);
}
