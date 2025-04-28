// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMEnemyActor.h"
#include "Game/DMGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ADMEnemyActor::ADMEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision")); // 충돌 박스 생성
	SetRootComponent(BoxComp); // 충돌 박스를 최상위 객체로
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f)); // 충돌 박스의 크기 설정
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component")); // 이 액터가 생성될 때 함께 따라오는 기본 구성 요소를 만드는 함수
	MeshComp->SetupAttachment(BoxComp); // MeshComp를 BoxComp에 붙인다 부모-자식 관계를 설정
}

// Called when the game starts or when spawned
void ADMEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	int32 DrawResult = 10; //FMath::RandRange(1, 100);
	if (DrawResult <= TraceRate)
	{
		TActorIterator<AActor> IActor(GetWorld());

		for (IActor; IActor; ++IActor)
		{
			if (IActor->GetActorLabel().Contains("Cube"))
			{
				Direction = IActor->GetActorLocation() - GetActorLocation();
				Direction.Normalize();
			}
		}

		if (Direction == FVector::ZeroVector)
		{
			Direction = GetActorForwardVector();
		}	
	}
	else
	{
		Direction = GetActorForwardVector();
	}

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADMEnemyActor::OnEnemyOverlap);
}

// Called every frame
void ADMEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector CurrentLocation = GetActorLocation();

	//FVector NewLocation = CurrentLocation + (Direction * MoveSpeed * DeltaTime);
	//SetActorLocation(NewLocation); // 새로운 위치로 적을 실제로 이동시킴

	//float TraveledDistance = FVector::Dist(StartLocation, CurrentLocation);

	//if (TraveledDistance >= MoveDistance)
	//{
	//	bMovingForward = !bMovingForward;
	//	StartLocation = CurrentLocation; // 기준 위치 갱신
	//}

	//Direction = bMovingForward ? MoveDirection : -MoveDirection;
	//FVector NewLocation = CurrentLocation + (Direction * MoveSpeed * DeltaTime);
	//SetActorLocation(NewLocation);
	CurrentDeltaTime = DeltaTime;
	Move();
}

void ADMEnemyActor::SetMoveSpeed(float NewSpeed)
{
	MoveSpeed = NewSpeed;
}

void ADMEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*AActor* IActor = Cast<AActor>(OtherActor);
	if (IActor != nullptr)
	{
		IActor->Destroy();
	}
	
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	ADMGameModeBase* DMGameMode = Cast<ADMGameModeBase>(CurrentGameMode);
	
	if (DMGameMode != nullptr)
	{

	}*/

	//Destroy();
}

//void ADMEnemyActor::MoveInAir()
//{
//	// 날아다니는 몬스터의 이동 방식 처리
//	FVector CurrentLocation = GetActorLocation();
//	FVector NewLocation2 = CurrentLocation + FVector(0.0f, 0.0f, 1.0f); // Z축을 따라 상승
//	SetActorLocation(NewLocation2); // 비행 시, 직접 위치 변경
//}
//
//void ADMEnemyActor::MoveOnGround()
//{
//	
//}

