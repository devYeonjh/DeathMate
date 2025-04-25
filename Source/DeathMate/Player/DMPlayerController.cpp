// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ADMPlayerController::ADMPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IAObj(TEXT("/Game/DoHoon/Input/Action/IA_Move2PHorizontal.IA_Move2P"));
	
	if (IAObj.Succeeded())
	{
		IA_LMMove2P = IAObj.Object;
	}
}

void ADMPlayerController::SetPlayer2P(APawn* const NewPlayer2P)
{
	ensure(NewPlayer2P);
	Player2P = NewPlayer2P;
}

void ADMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent && IA_LMMove2P)
	{
		EnhancedInputComponent->BindAction(IA_LMMove2P, ETriggerEvent::Triggered, this, &ADMPlayerController::OnInputMove2P);
		
	}
}

void ADMPlayerController::OnInputMove2P(const FInputActionValue& Value)
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
	}
}



