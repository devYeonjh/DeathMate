// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMBlinkingEnemy.h"
#include "Components/MeshComponent.h"


void ADMBlinkingEnemy::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// 메시 컴포넌트에서 동적 머티리얼 생성
	//UMeshComponent* MeshComp = FindComponentByClass<UMeshComponent>();
	if (MeshComp)
	{
		DynMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(0); // 0번째 머티리얼 슬롯 사용
	}


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
	SetActorLocation(NewLocation);
	UpdateVisibility(CurrentDeltaTime);
}

void ADMBlinkingEnemy::UpdateVisibility(float DeltaTime)
{
	//TimeSinceLastToggle += DeltaTime;

	//if (TimeSinceLastToggle >= ToggleInterval)
	//{
	//	TimeSinceLastToggle = 0.0f;
	//	bVisible = !bVisible;

	//	SetActorHiddenInGame(!bVisible); // 렌더링 ON/OFF
	//	SetActorEnableCollision(bVisible); // 충돌 ON/OFF
	//}

	TimeSinceLastToggle += DeltaTime;

	if (TimeSinceLastToggle >= ToggleInterval)
	{
		TimeSinceLastToggle = 0.0f;
		bVisible = !bVisible;

		// 머티리얼 Opacity 조절
		if (DynMaterial)
		{
			float NewOpacity = bVisible ? 1.0f : 0.0f;
			DynMaterial->SetScalarParameterValue(TEXT("OpacityParam"), NewOpacity);
		}

		// 충돌 ON/OFF
	/*	UMeshComponent* MeshComp = FindComponentByClass<UMeshComponent>();
		if (MeshComp)
		{*/
			MeshComp->SetCollisionEnabled(bVisible ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
		//}
	}
}
