// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMFlyEnemy.h"

void ADMFlyEnemy::Move()
{
	// ���ƴٴϴ� ������ �̵� ��� ó��
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation2 = CurrentLocation + FVector(0.0f, 0.0f, 1.0f); // Z���� ���� ���
	SetActorLocation(NewLocation2); // ���� ��, ���� ��ġ ����
}
