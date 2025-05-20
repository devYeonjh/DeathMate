// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMFollowingCamera.h"
#include "Game/DMGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PaperTileMapActor.h"
#include "EngineUtils.h"

// Sets default values
ADMFollowingCamera::ADMFollowingCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(RootComponent);

	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 1920.f;
	CameraComponent->bAutoCalculateOrthoPlanes = false;
	CameraComponent->bUseCameraHeightAsViewTarget = false;
}

// Called when the game starts or when spawned
void ADMFollowingCamera::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<APaperTileMapActor> It(GetWorld()); It; ++It)
	{
		TileMapActor = *It;
		break;
	}

	if (TileMapActor)
	{
		FBox MapBounds = TileMapActor->GetComponentsBoundingBox();

		MinX = MapBounds.Min.X;
		MaxX = MapBounds.Max.X;
		MinZ = MapBounds.Min.Z;  
		MaxZ = MapBounds.Max.Z;  
	}

	if (CameraComponent)
	{
		CameraHalfWidth = CameraComponent->OrthoWidth * 0.5f;
		CameraHalfHeight = CameraHalfWidth / CameraComponent->AspectRatio; 
	}

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			TargetActor = Pawn;
		}
	}
	if (TargetActor)
	{
		SetActorLocation(TargetActor->GetActorLocation() + FollowOffset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FollowingCamera: TargetActor가 null입니다. 카메라 위치를 설정할 수 없습니다."));
	}


	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PC->SetViewTarget(this);
	}

	if (ADMGameModeBase* GM = Cast<ADMGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GM->SpawnCheckPointDelegate.AddUObject(this, &ADMFollowingCamera::RespawnAction);
	}
	
}

// Called every frame
void ADMFollowingCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bTriedBeginPlayPawnSetup && !TargetActor)
	{
		bTriedBeginPlayPawnSetup = true;
		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* Pawn = PC->GetPawn())
			{
				TargetActor = Pawn;
				SetActorLocation(TargetActor->GetActorLocation() + FollowOffset);
				UE_LOG(LogTemp, Log, TEXT("FollowingCamera: Tick에서 TargetActor를 재바인딩했습니다."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("FollowingCamera: Tick 시도에도 Pawn이 없습니다."));
			}
		}
	}


	if (!TargetActor) return;

	const FVector TargetLoc = TargetActor->GetActorLocation();
	const FVector DesiredLocation = TargetLoc + FollowOffset;
	const FVector NewLocation = (SmoothSpeed > 0.f)
		? FMath::VInterpTo(GetActorLocation(), DesiredLocation, DeltaTime, SmoothSpeed)
		: DesiredLocation;

	FVector Clamped = NewLocation;
	Clamped.X = FMath::Clamp(
		NewLocation.X,
		MinX + CameraHalfWidth,
		MaxX - CameraHalfWidth
	);
	Clamped.Z = FMath::Clamp(
        NewLocation.Z,
        MinZ + CameraHalfHeight,
        MaxZ - CameraHalfHeight
    );

	SetActorLocation(Clamped);
}

void ADMFollowingCamera::RespawnAction(const FVector& Checkpoint)
{
	const FVector DesiredLocation = Checkpoint + FollowOffset;

	FVector Clamped = DesiredLocation;
	Clamped.X = FMath::Clamp(
		DesiredLocation.X,
		MinX + CameraHalfWidth,
		MaxX - CameraHalfWidth
	);
	Clamped.Z = FMath::Clamp(
		DesiredLocation.Z,
		MinZ + CameraHalfHeight,
		MaxZ - CameraHalfHeight
	);

	SetActorLocation(Clamped);
}

