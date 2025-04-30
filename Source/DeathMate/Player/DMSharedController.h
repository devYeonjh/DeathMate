// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DMSharedController.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMSharedController : public APlayerController
{
	GENERATED_BODY()

public:
	ADMSharedController();

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Idle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Dash;

private:
	void OnInputMoveTriggered(const FInputActionValue& Value);

	void OnInputDash(const FInputActionValue& Value);


	
};
