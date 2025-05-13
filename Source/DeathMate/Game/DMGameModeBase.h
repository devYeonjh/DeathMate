// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DMGameModeBase.generated.h"

class ADMFollowingCamera;
class APaperCharacter;

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
	TSubclassOf<APaperCharacter> PlayerCharacter1P;
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<APaperCharacter> PlayerCharacter2P;

	UPROPERTY(EditAnywhere, Category = "Player")
	class APlayerStart* PlayerStart1P;
	UPROPERTY(EditAnywhere, Category = "Player")
	class APlayerStart* PlayerStart2P;	

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<ADMFollowingCamera> FollowingCameraClass;

private:
	int32 SpawnedPlayerIndex = 0;

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	APlayerStart* FindPlayerStart(UWorld* World, const FName& TargetTag);

	void SpawnLocalPlayer(int32 PlayerIndex, APlayerStart* PlayerStart, UWorld* World);

	APaperCharacter* SpawnAndPosessPawn(UWorld* World, APlayerController* PlayerController, APlayerStart* PlayerStart, int32 PlayerIndex);

private:
	FVector Checkpoint;
	APaperCharacter* Player1;
	APaperCharacter* Player2;
	ADMFollowingCamera* MainCamera;

public:
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpoint(const FVector& Pos);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtCheckpoint();

	FORCEINLINE ADMFollowingCamera* GetMainCamera() const { return MainCamera; }

};
