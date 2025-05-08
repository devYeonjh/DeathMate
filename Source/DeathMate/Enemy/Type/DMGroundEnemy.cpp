// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Type/DMGroundEnemy.h"
#include "DrawDebugHelpers.h"

void ADMGroundEnemy::BeginPlay()
{
	Super::BeginPlay();

	Direction = FVector(1, 0, 0); // 기본 X축 방향
}

void ADMGroundEnemy::Move()
{

	FVector CurrentLocation = GetActorLocation();

	// 낙하 확인용 라인 트레이스(바닥 체크)
	FVector Start = CurrentLocation + FVector(Direction.X * 20.0f, 0.0f, 0.0f); // 앞으로 약간 이동
	FVector End = Start + FVector(0.0f, 0.0f, -50.0f); // 아래 방향

	FHitResult FloorHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bOnGround = GetWorld()->LineTraceSingleByChannel(FloorHit, Start, End, ECC_GameTraceChannel2, Params);

	// 벽 충돌 확인용 라인 트레이스(전방 장애물)
	FVector WallCheckStart = CurrentLocation;
	FVector WallCheckEnd = CurrentLocation + Direction * 20.0f;

	FHitResult WallHit;
	// ECollisionChannel TraceChannel 이 파라미터에 ECC_GameTraceChannel2[Enemy]
	// Enemy의 Objecy Type인 레이져가 발사가 될 것이다.
	bool bHitWall = GetWorld()->LineTraceSingleByChannel(WallHit, WallCheckStart, WallCheckEnd, ECC_GameTraceChannel2, Params);

#if (WITH_EDITOR)
	{
		// 디버그 시각화(필요 시)
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f, 0, 1.0f);
		DrawDebugLine(GetWorld(), WallCheckStart, WallCheckEnd, FColor::Red, false, 0.1f, 0, 1.0f);
	}
#endif

	// 방향 전환 조건
	if (!bOnGround || bHitWall)
	{
		Direction *= -1.0f;
	}

	FVector NewLocation = CurrentLocation + (Direction * MoveSpeed * CurrentDeltaTime);
	SetActorLocation2D(NewLocation);

	UE_LOG(LogTemp, Warning, TEXT("MoveSpeed: %f, Direction: %s"), MoveSpeed, *Direction.ToString());

}
