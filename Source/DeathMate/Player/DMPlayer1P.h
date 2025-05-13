// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DMPlayerBase.h"
#include "InputActionValue.h"
#include "Interface/DMDamagedActor.h"
#include "DMPlayer1P.generated.h"

class UInputAction;
class UPaperFlipbook;
class ADMGameModeBase;

/**
 *
 */
UCLASS()
class DEATHMATE_API ADMPlayer1P : public ADMPlayerBase, public IDMDamagedActor
{
	GENERATED_BODY()

public:
	ADMPlayer1P();
	
protected:
	virtual void BeginPlay() override;
	virtual void RespawnAction(const FVector& Checkpoint) override;

private:
	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionValue& Value);

private:
	ADMGameModeBase* DMGM;

public:
	virtual void TakeDamage() override;
};
