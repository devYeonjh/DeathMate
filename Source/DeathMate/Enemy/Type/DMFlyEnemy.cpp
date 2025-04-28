// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMFlyEnemy.h"

void ADMFlyEnemy::Move()
{
	// 날아다니는 몬스터의 이동 방식 처리
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation2 = CurrentLocation + FVector(0.0f, 0.0f, 1.0f); // Z축을 따라 상승
	SetActorLocation(NewLocation2); // 비행 시, 직접 위치 변경
}
