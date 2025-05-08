// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayerController.h"
#include "Player/DMPaperCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
ADMPlayerController::ADMPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IAMoveObj(TEXT("/Game/Input/Action/IA_Move2P.IA_Move2P"));
	
	if (IAMoveObj.Succeeded())
	{
		IA_DMMove2P = IAMoveObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IADashObj(TEXT("/Game/Input/Action/IA_Dash.IA_Dash"));
	if (IADashObj.Succeeded())
	{
		IA_Dash2P = IADashObj.Object;
	}

}

void ADMPlayerController::SetPlayer2P(ADMPaperCharacter* const NewPlayer2P)
{
	ensure(NewPlayer2P);
	Player2P = NewPlayer2P;
}

void ADMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent && IA_DMMove2P)
	{
		EnhancedInputComponent->BindAction(IA_DMMove2P, ETriggerEvent::Triggered, this, &ADMPlayerController::OnInputMoveTriggered);
	}
}

void ADMPlayerController::OnInputMoveStarted(const FInputActionValue& Value)
{

}

void ADMPlayerController::OnInputMoveTriggered(const FInputActionValue& Value)
{
	if (Player2P)
	{
		FVector2D MoveVector = Value.Get<FVector2D>(); // ex) (1,0) (-1, 0) (0, 1) (0, -1)

		FVector ForwardDirection = Player2P->GetActorForwardVector() * MoveVector.X;
		FVector UpDirection = Player2P->GetActorUpVector() * MoveVector.Y;
		FVector MoveDirection = ForwardDirection + UpDirection;

		if (MoveDirection.SizeSquared() > 0.0f)
		{
			Player2P->AddMovementInput(MoveDirection.GetSafeNormal());
		}

		float Yaw = (MoveDirection.X < 0.f) ? 0.f : 180.f;
		Player2P->GetSprite()->SetRelativeRotation(FRotator(0.f, Yaw, 0.f));
	}
}

void ADMPlayerController::OnInputMoveCompleted(const FInputActionValue& Value)
{

}

void ADMPlayerController::OnInputDash(const FInputActionValue& Value)
{
	if (Player2P)
	{

	}

}
