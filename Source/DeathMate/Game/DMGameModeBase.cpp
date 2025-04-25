// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DMGameModeBase.h"
#include "Player/DMPaperCharacter.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Player/DMPlayerController.h"


ADMGameModeBase::ADMGameModeBase()
{
	
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
	SpawnLocalPlayer(SpawnedPlayerIndex++, PlayerStart2P, World);

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
		UGameInstance* GameInstance = GetGameInstance();
		ensure(GameInstance);
		FString Error;
		ULocalPlayer* NewLocalPlayer = GameInstance->CreateLocalPlayer(-1, Error, true);
		ensure(NewLocalPlayer);
		APlayerController* PlayerController2P = NewLocalPlayer->GetPlayerController(World);
		SpawnAndPosessPawn(World, PlayerController2P, PlayerStart, PlayerIndex);
	}

}

ADMPaperCharacter* ADMGameModeBase::SpawnAndPosessPawn(UWorld* World, APlayerController* PlayerController, APlayerStart* PlayerStart, int32 PlayerIndex)
{
	if (!World || !PlayerController || !PlayerStart)
	{

		UE_LOG(LogTemp, Warning, TEXT("파라미터 중 유효하지 않은 인자가 있습니다."));
		return nullptr;
	}
	ADMPaperCharacter* PlayerPawn = World->SpawnActor<ADMPaperCharacter>(DMPaperCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
	ensure(PlayerPawn);
	PlayerPawn->SetPlayerIndex(PlayerIndex);
	PlayerController->Possess(PlayerPawn);

	return PlayerPawn;
}

