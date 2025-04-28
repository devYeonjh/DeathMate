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
	class APawn* Player2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_DMMove2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_Flip2P;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayer2P(class APawn* const NewPlayer2P);

protected:
	virtual void SetupInputComponent() override;

private:
	void OnInputMove2P(const FInputActionValue& Value);
	void Flip(const FInputActionValue& Value);
	
};
