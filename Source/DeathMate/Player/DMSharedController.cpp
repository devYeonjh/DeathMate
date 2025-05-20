// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMSharedController.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/PauseMenuWidget.h"  
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/DMPlayerBase.h"

#include "Blueprint/UserWidget.h"
#include "UI/HpBarWidget.h"

ADMSharedController::ADMSharedController()
{
	static ConstructorHelpers::FClassFinder<UPauseMenuWidget> PauseBP(TEXT("/Game/UI/WB_PauseMenu.WB_PauseMenu_C"));
	if (PauseBP.Succeeded())
	{
		PauseMenuClass = PauseBP.Class;
	}
}

void ADMSharedController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	if (PauseMenuClass)
	{
		PauseMenuInstance = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseMenuClass);
		if (PauseMenuInstance)
		{
			PauseMenuInstance->AddToViewport();

			PauseMenuInstance->ResumeGame();
		}
	}

	if (HpBarWidgetClass)
	{
		HpBarWidgetInstance = CreateWidget<UHpBarWidget>(GetWorld(), HpBarWidgetClass);
		if (HpBarWidgetInstance)
		{
			HpBarWidgetInstance->AddToViewport();
		}
	}

}


void ADMSharedController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		//--------------------------Player 1P Input--------------------------
		EnhancedInputComponent->BindActionValueLambda(IA_Move1P, ETriggerEvent::Started, [this](const FInputActionValue& Value)->void { OnInputMoveStarted1PAction.Broadcast(Value); });
		EnhancedInputComponent->BindActionValueLambda(IA_Move1P, ETriggerEvent::Triggered, [this](const FInputActionValue& Value)->void { OnInputMoveTriggered1PAction.Broadcast(Value); });
		EnhancedInputComponent->BindActionValueLambda(IA_Move1P, ETriggerEvent::Completed, [this](const FInputActionValue& Value)->void { OnInputMoveCompleted1PAction.Broadcast(Value); });
		
		EnhancedInputComponent->BindActionValueLambda(IA_Jump1P, ETriggerEvent::Started, [this](const FInputActionValue& Value)->void { OnInputJumpStarted1PAction.Broadcast(Value); });
		EnhancedInputComponent->BindActionValueLambda(IA_Jump1P, ETriggerEvent::Completed, [this](const FInputActionValue& Value)->void { OnInputJumpCompleted1PAction.Broadcast(Value); });

		//--------------------------Player 2P Input--------------------------
		EnhancedInputComponent->BindActionValueLambda(IA_Move2P, ETriggerEvent::Started, [this](const FInputActionValue& Value)->void { OnInputMoveStarted2PAction.Broadcast(Value); });
		EnhancedInputComponent->BindActionValueLambda(IA_Move2P, ETriggerEvent::Triggered, [this](const FInputActionValue& Value)->void {OnInputMoveTriggered2PAction.Broadcast(Value); });
		EnhancedInputComponent->BindActionValueLambda(IA_Move2P, ETriggerEvent::Completed, [this](const FInputActionValue& Value)->void { OnInputMoveCompleted2PAction.Broadcast(Value); });
	
		EnhancedInputComponent->BindActionValueLambda(IA_Attack2P, ETriggerEvent::Started, [this](const FInputActionValue& Value)->void { OnInputAttackStarted2PAction.Broadcast(Value); });
	}
	InputComponent->BindAction("Pause", IE_Pressed, this, &ADMSharedController::HandlePause);
}


void ADMSharedController::HandlePause()
{
	if (!PauseMenuInstance)
		return;

	if (!UGameplayStatics::IsGamePaused(this))
		PauseMenuInstance->ShowPauseMenu();
	else
		PauseMenuInstance->ResumeGame();
}