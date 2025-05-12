// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DMPlayerBase.h"
#include "InputActionValue.h"
#include "DMPlayer2P.generated.h"

class UInputAction;
class UCameraComponent;
class UPaperFlipbook;
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

private:
	UCameraComponent* MyCam;

	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionValue& Value);
};
