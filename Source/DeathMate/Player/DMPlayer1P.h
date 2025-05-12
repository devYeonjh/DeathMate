// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DMPlayerBase.h"
#include "InputActionValue.h"
#include "DMPlayer1P.generated.h"

class UInputAction;
class UPaperFlipbook;

/**
 *
 */
UCLASS()
class DEATHMATE_API ADMPlayer1P : public ADMPlayerBase
{
	GENERATED_BODY()

public:
	ADMPlayer1P();
	
protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionValue& Value);
};
