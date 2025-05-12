// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DMGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADMGameModeBase();

public:
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class APaperCharacter> PlayerCharacter1P;
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class APaperCharacter> PlayerCharacter2P;

	UPROPERTY(EditAnywhere, Category = "Player")
	class APlayerStart* PlayerStart1P;
	UPROPERTY(EditAnywhere, Category = "Player")
	class APlayerStart* PlayerStart2P;	

private:
	int32 SpawnedPlayerIndex = 0;

protected:
	virtual void BeginPlay() override;

private:
	APlayerStart* FindPlayerStart(UWorld* World, const FName& TargetTag);

	void SpawnLocalPlayer(int32 PlayerIndex, APlayerStart* PlayerStart, UWorld* World);

	class APaperCharacter* SpawnAndPosessPawn(UWorld* World, APlayerController* PlayerController, APlayerStart* PlayerStart, int32 PlayerIndex);

private:
	FVector Checkpoint;
	class APaperCharacter* Player1;
	class APaperCharacter* Player2;

public:
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpoint(const FVector& Pos);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtCheckpoint();


};
