// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DMGameModeBase.h"
#include "Player/DMSharedController.h"
#include "Player/DMFollowingCamera.h"
#include "Player/DMPlayerBase.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"


ADMGameModeBase::ADMGameModeBase()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ADMSharedController::StaticClass();
	SpectatorClass = nullptr;
}

void ADMGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	const FName TargetTag1P = TEXT("PlayerStart1P");
	const FName TargetTag2P = TEXT("PlayerStart2P");

	PlayerStart1P = FindPlayerStart(World, TargetTag1P);
	PlayerStart2P = FindPlayerStart(World, TargetTag2P);

	SpawnLocalPlayer(SpawnedPlayerIndex++, PlayerStart1P, World);
	SpawnLocalPlayer(SpawnedPlayerIndex, PlayerStart2P, World);

}

void ADMGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (MainCamera)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;

	TArray<AActor*> FoundCams;
	UGameplayStatics::GetAllActorsOfClass(World, FollowingCameraClass, FoundCams);
	if (FoundCams.Num() > 0)
	{
		return;
	}

	APawn* Target = NewPlayer->GetPawn();

	if (FollowingCameraClass && NewPlayer)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		MainCamera = GetWorld()->SpawnActor<ADMFollowingCamera>(
			FollowingCameraClass,
			FVector::ZeroVector, FRotator(0.f, -90.f, 0.f),
			Params
		);

		if (MainCamera)
		{
			MainCamera->TargetActor = Target;
			NewPlayer->SetViewTarget(MainCamera);
		}
	}
}

APlayerStart* ADMGameModeBase::FindPlayerStart(UWorld* World, const FName& TargetTag)
{
	if (!World) // World == nullptr
	{
		UE_LOG(LogTemp, Warning, TEXT("UWorld is nullptr "));
		return nullptr;
	}
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* FoundStart = *It;
		if (FoundStart && FoundStart->PlayerStartTag == TargetTag)
		{
			return FoundStart;
		}
	}

	return nullptr;
}

void ADMGameModeBase::SpawnLocalPlayer(int32 PlayerIndex, APlayerStart* PlayerStart, UWorld* World)
{
	if (!PlayerStart || !World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Parameter."));
		return;
	}

	if (PlayerIndex == 0)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, PlayerIndex);
		SpawnAndPosessPawn(World, PlayerController, PlayerStart, PlayerIndex);
	}
	else if (PlayerIndex == 1)
	{
		UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
		ensure(GameInstance);
		FString Error;
		ULocalPlayer* NewLocalPlayer = GameInstance->CreateLocalPlayer(-1, Error, true);
		ensure(NewLocalPlayer);
		APlayerController* PlayerController2P = NewLocalPlayer->PlayerController;
		SpawnAndPosessPawn(World, PlayerController2P, PlayerStart, PlayerIndex);
	}

}

ADMPlayerBase* ADMGameModeBase::SpawnAndPosessPawn(UWorld* World, APlayerController* PlayerController, APlayerStart* PlayerStart, int32 PlayerIndex)
{
	if (!World || !PlayerController || !PlayerStart)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Parameters"));
		return nullptr;
	}

	TSubclassOf<ADMPlayerBase> SpawnCharacter = nullptr;

	if (PlayerIndex == 0)
	{
		SpawnCharacter = PlayerCharacter1P;
	}
	else if (PlayerIndex == 1)
	{
		SpawnCharacter = PlayerCharacter2P;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Player Index"));
		return nullptr;
	}

	ADMPlayerBase* PlayerPawn =
		World->SpawnActor<ADMPlayerBase>(SpawnCharacter,
			PlayerStart->GetActorLocation(),
			PlayerStart->GetActorRotation());
	ensure(PlayerPawn);

	PlayerController->Possess(PlayerPawn);

	// 처음 생성된 위치를 체크포인트 설정
	if (PlayerIndex == 0)
	{
		SetCheckpoint(PlayerStart->GetActorLocation());
	}

	return PlayerPawn;
}

void ADMGameModeBase::SetCheckpoint(const FVector& Pos)
{
	Checkpoint = Pos;
}

//플레이어가 체크포인트에서 리스폰
void ADMGameModeBase::RespawnAtCheckpoint()
{
	SpawnCheckPointDelegate.Broadcast(Checkpoint);
}

