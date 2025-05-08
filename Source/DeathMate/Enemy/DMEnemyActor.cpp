// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMEnemyActor.h"
#include "Game/DMGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Player/DMPaperCharacter.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ADMEnemyActor::ADMEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f)); // 충돌 박스의 크기 설정

	BoxComp->SetCollisionProfileName(TEXT("Enemy")); // 충돌 프로필 설정
}

// Called when the game starts or when spawned
void ADMEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADMEnemyActor::OnEnemyOverlap);
}

void ADMEnemyActor::SetActorLocation2D(FVector Pos)
{
	float CurX = GetActorLocation().X;

	FVector Dir = CurX < Pos.X ? FVector(1.0f, 1.0f, 1.0f) : FVector(-1.0f, 1.0f, 1.0f);

	if (FlipbookComp)
	{
		FlipbookComp->SetRelativeScale3D(Dir);
	}

	SetActorLocation(Pos);
}

// Called every frame
void ADMEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDeltaTime = DeltaTime;
	Move();

	LifeTimer += DeltaTime;
	if (LifeTimer >= LifeTime)
	{
		Destroy();
	}
}

void ADMEnemyActor::SetMoveSpeed(float NewSpeed)
{
	MoveSpeed = NewSpeed;
}

void ADMEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor)
	{
		ADMPaperCharacter* Player1P = Cast<ADMPaperCharacter>(OtherActor);
		ensure(Player1P);

		//체크포인트로 되돌아가는 함수
		UWorld* world = GetWorld();
		ADMGameModeBase* DMGameMode = Cast<ADMGameModeBase>(UGameplayStatics::GetGameMode(world));
	}
}

void ADMEnemyActor::Death()
{
	//죽엇을때 이펙트 or 파티클 추가

	Destroy();
}

