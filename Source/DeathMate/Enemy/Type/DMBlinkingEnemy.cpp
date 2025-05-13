// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMBlinkingEnemy.h"
#include "Components/MeshComponent.h"


void ADMBlinkingEnemy::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//if (MeshComp)
	//{
	//	DynMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(0); // 0번째 머티리얼 슬롯 사용
	//}

}

void ADMBlinkingEnemy::Move()
{
	FVector CurrentLocation = GetActorLocation();
	float TraveledDistance = FVector::Dist(StartLocation, CurrentLocation);

	if (TraveledDistance >= MoveDistance)
	{
		bMovingForward = !bMovingForward;
		StartLocation = CurrentLocation;
	}
	if (bMovingForward)
	{
		Direction = MoveDirection;
	}
	else
	{
		Direction = -MoveDirection;
	}
	FVector NewLocation = CurrentLocation + (Direction * MoveSpeed * CurrentDeltaTime);
	SetActorLocation2D(NewLocation);
	UpdateVisibility(CurrentDeltaTime);
}

void ADMBlinkingEnemy::UpdateVisibility(float DeltaTime)
{

	TimeSinceLastToggle += DeltaTime;

	if (TimeSinceLastToggle >= ToggleInterval)
	{
		TimeSinceLastToggle = 0.f;
		bVisible = !bVisible;

		if (DynMaterial)
		{
			float NewOpacity = bVisible ? 1.f : 0.f;
			DynMaterial->SetScalarParameterValue(TEXT("OpacityParam"), NewOpacity);
		}

		// UMeshComponent* MeshComp = FindComponentByClass<UMeshComponent>();
		/*if (MeshComp)
		{
			MeshComp->SetCollisionEnabled(bVisible ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
		}*/
	}

}
