// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADMPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Player")
	class ADMPaperCharacter* Player2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_DMMove2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_Dash2P;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayer2P(class ADMPaperCharacter* const NewPlayer2P);

protected:
	virtual void SetupInputComponent() override;

private:
	void OnInputMoveStarted(const FInputActionValue& Value);
	void OnInputMoveTriggered(const FInputActionValue& Value);
	void OnInputMoveCompleted(const FInputActionValue& Value);

	void OnInputDash(const FInputActionValue& Value);
};
