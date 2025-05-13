// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DMPlayerBase.h"
#include "InputActionValue.h"
#include "DMPlayer2P.generated.h"

class UInputAction;
class UPaperFlipbook;
class APaperFlipbookActor;
class ADMFollowingCamera;
/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMPlayer2P : public ADMPlayerBase
{
	GENERATED_BODY()

public:
	ADMPlayer2P();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void RespawnAction(const FVector& Checkpoint) override;

private:
	ADMFollowingCamera* MyCam;

	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionValue& Value);

private:
	bool bIsAttacking = false;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetAttackFinished() { bIsAttacking = false; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	void Attack();
	UPROPERTY(EditDefaultsOnly, Category = "Combat|VFX")
	TSubclassOf<APaperFlipbookActor> AttackFlipbookActorClass;
	UPROPERTY(EditDefaultsOnly, Category = "Combat|VFX")
	UPaperFlipbook* AttackFlipbookAsset;

};
