// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "DMGameModeBase.generated.h"

class ADMFollowingCamera;
class ADMPlayerBase;
class APlayerStart;

DECLARE_MULTICAST_DELEGATE_OneParam(FSpawnCheckPointDelegate, const FVector&);


UCLASS()
class DEATHMATE_API ADMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADMGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<ADMPlayerBase> PlayerCharacter1P;
	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<ADMPlayerBase> PlayerCharacter2P;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TSubclassOf<ADMFollowingCamera> FollowingCameraClass;

private:
	int32 SpawnedPlayerIndex = 0;
	APlayerStart* PlayerStart1P;
	APlayerStart* PlayerStart2P;

private:
	APlayerStart* FindPlayerStart(UWorld* World, const FName& TargetTag);

	void SpawnLocalPlayer(int32 PlayerIndex, APlayerStart* PlayerStart, UWorld* World);

	ADMPlayerBase* SpawnAndPosessPawn(UWorld* World, APlayerController* PlayerController, APlayerStart* PlayerStart, int32 PlayerIndex);

private:
	FVector Checkpoint;
	FVector FirstCheckpoint;
	ADMFollowingCamera* MainCamera;

public:
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void SetCheckpoint(const FVector& Pos);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnAtFirstCheckpoint();

	FSpawnCheckPointDelegate SpawnCheckPointDelegate;

	FORCEINLINE ADMFollowingCamera* GetMainCamera() const { return MainCamera; }

};
