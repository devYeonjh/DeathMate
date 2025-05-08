// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PaperFlipbook.h"
#include "DMInputComponent.generated.h"


UCLASS( ClassGroup=(Input), meta=(BlueprintSpawnableComponent) )
class DEATHMATE_API UDMInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDMInputComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputComponent", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_PlayerInput;

	// Player 1
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Move1P;
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Jump1P;
	
	// Player 2
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Move2P;
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* IA_Dash2P;


	void InitializeInput(class UEnhancedInputComponent* EIC, int32 PlayerIndex);

private:
    void OnMove1P(const FInputActionInstance& Instance);
    void OnStopMove1P(const FInputActionInstance& Instance);
    void OnJump1P(const FInputActionInstance& Instance);
    void OnStopJump1P(const FInputActionInstance& Instance);
    
    void OnMove2P(const FInputActionInstance& Instance);
    void OnDash2P(const FInputActionInstance& Instance);

		
};
