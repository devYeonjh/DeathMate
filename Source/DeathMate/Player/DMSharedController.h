// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "DMSharedController.generated.h"


class UPauseMenuWidget;
class ADMPlayerBase;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
/**
 * 
 */


DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputMoveStarted1P, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputMoveTriggered1P, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputMoveCompleted1P, const FInputActionValue&);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputJumpStarted1P, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputJumpCompleted1P, const FInputActionValue&);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputMoveStarted2P, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputMoveTriggered2P, const FInputActionValue&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputMoveCompleted2P, const FInputActionValue&);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputAttackStarted2P, const FInputActionValue&);


UCLASS()
class DEATHMATE_API ADMSharedController : public APlayerController
{
	GENERATED_BODY()

public:
	ADMSharedController();
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPauseMenuWidget> PauseMenuClass;

	UPROPERTY()
	UPauseMenuWidget* PauseMenuInstance = nullptr;

	
	FOnInputMoveStarted1P OnInputMoveStarted1PAction;
	FOnInputMoveTriggered1P OnInputMoveTriggered1PAction;
	FOnInputMoveCompleted1P OnInputMoveCompleted1PAction;

	FOnInputJumpStarted1P OnInputJumpStarted1PAction;
	FOnInputJumpCompleted1P OnInputJumpCompleted1PAction;

	FOnInputMoveStarted2P OnInputMoveStarted2PAction;
	FOnInputMoveTriggered2P OnInputMoveTriggered2PAction;
	FOnInputMoveCompleted2P OnInputMoveCompleted2PAction;

	FOnInputAttackStarted2P OnInputAttackStarted2PAction;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	ADMPlayerBase* Player1P;
	UPROPERTY(VisibleAnywhere, Category = "Player")
	ADMPlayerBase* Player2P;

private:
	//--------------------------Player 1P Input--------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move1P;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Jump1P;

private:
	//--------------------------Player 2P Input--------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Move2P;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Dash2P;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Attack2P;

	UCameraComponent* MyCam;


public:
	virtual void SetupInputComponent() override;


	UFUNCTION()
	void HandlePause();

	
};
