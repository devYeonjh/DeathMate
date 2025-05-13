// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DMPlayerBase.generated.h"

class UInputMappingContext;
class UInputComponent;
class UEnhancedInputComponent;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMPlayerBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ADMPlayerBase();

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION()
	virtual void RespawnAction(const FVector& Checkpoint);

protected:
	UPROPERTY(BlueprintGetter = GetIsRunning, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsRunning = false;
	
	UCharacterMovementComponent* MoveComp;

private:
	UInputMappingContext* IMC_PlayerInput;

public:
	UFUNCTION(BlueprintGetter, Category = "Movement")
	bool GetIsRunning() const { return bIsRunning; }


	
};
