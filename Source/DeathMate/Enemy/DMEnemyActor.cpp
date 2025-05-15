// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/DMEnemyActor.h"
#include "Enemy/DMEnemyFactory.h"
#include "Game/DMGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Player/DMPlayer1P.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ADMEnemyActor::ADMEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComp->SetBoxExtent(FVector(50.f, 50.f, 50.f)); // 충돌 박스의 크기 설정

	//BoxComp->SetCollisionProfileName(TEXT("Enemy")); // 충돌 프로필 설정

	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComp"));
	FlipbookComp->SetupAttachment(RootComponent);
	FlipbookComp->SetCollisionProfileName(TEXT("Enemy"));;
}

// Called when the game starts or when spawned
void ADMEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	FlipbookComp->OnComponentBeginOverlap.AddDynamic(this, &ADMEnemyActor::OnEnemyOverlap);
	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADMEnemyActor::OnEnemyOverlap);
}

void ADMEnemyActor::SetActorLocation2D(FVector Pos)
{
	float CurX = GetActorLocation().X;

	//FVector Dir = CurX < Pos.X ? FVector(1.f, 1.f, 1.f) : FVector(-1.f, 1.f, 1.f);
	FVector Dir = CurX < Pos.X ? GetActorRelativeScale3D() : GetActorRelativeScale3D() * FVector(-1.f, 1.f, 1.f);

	
	if (FlipbookComp)
	{
		//FlipbookComp->SetRelativeScale3D(Dir);
		float Yaw = (CurX < Pos.X) ? 0.f : 180.f;
		SetActorRotation(FRotator(0.f, Yaw, 0.f));
	}

	SetActorLocation(Pos);
}

// Called every frame
void ADMEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDeltaTime = DeltaTime;
	Move();
}


void ADMEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor)
	{
		ADMPlayer1P* Player1P = Cast<ADMPlayer1P>(OtherActor);
		if (Player1P)
		{
			Player1P->TakeDamage();
		}
	}
}

void ADMEnemyActor::TakeDamage()
{
	UE_LOG(LogTemp, Warning, TEXT("TakeDamage"));

	OnEnemyDieAction.Broadcast();
	OnEnemyDieAction.Clear();
	Destroy();
}


