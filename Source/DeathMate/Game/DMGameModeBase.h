// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	TSubclassOf<class ADMPaperCharacter> DMPaperCharacterClass;

	UPROPERTY(EditAnywhere, Category = "Player")
	class APlayerStart* PlayerStart1P;
	UPROPERTY(EditAnywhere, Category = "Player")
	class APlayerStart* PlayerStart2P;

private:
	int32 SpawnedPlayerIndex = 0;

protected:
	virtual void BeginPlay() override;

private:
	// 태그를 이용해서 PlayerStart 찾는 함수
	APlayerStart* FindPlayerStart(UWorld* World, const FName& TargetTag);

	// 로컬 플레이어를 스폰하는 함수
	void SpawnLocalPlayer(int32 PlayerIndex, APlayerStart* PlayerStart, UWorld* World);

	// Possessed를 시키는 함수
	class ADMPaperCharacter* SpawnAndPosessPawn(UWorld* World, APlayerController* PlayerController, APlayerStart* PlayerStart, int32 PlayerIndex);
};
