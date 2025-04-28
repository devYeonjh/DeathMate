// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ADMPlayerController::ADMPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> IAObj(TEXT("/Game/Input/Action/IA_Move2P.IA_Move2P"));
	
	if (IAObj.Succeeded())
	{
		IA_DMMove2P = IAObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAFlipObj(TEXT("/Game/Input/Action/IA_Flip2P.IA_Flip2P"));
	if (IAFlipObj.Succeeded())
	{
		IA_Flip2P = IAFlipObj.Object;
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
	if (EnhancedInputComponent && IA_DMMove2P && IA_Flip2P)
	{
		EnhancedInputComponent->BindAction(IA_DMMove2P, ETriggerEvent::Triggered, this, &ADMPlayerController::OnInputMove2P);
		EnhancedInputComponent->BindAction(IA_Flip2P, ETriggerEvent::Triggered, this, &ADMPlayerController::Flip);
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

void ADMPlayerController::Flip(const FInputActionValue& Value)
{
	if (Player2P)
	{
		FVector2D MoveVector = Value.Get<FVector2D>(); // ex) (1,0) (-1, 0) (0, 1) (0, -1)

		float MoveDir = MoveVector.X;

		if (MoveDir > 0.0f)
		{
			Player2P->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f), false);
			UE_LOG(LogTemp, Warning, TEXT("Flip Player2P %f"), MoveDir);
		}
		else if (MoveDir < 0.0f)
		{
			Player2P->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 180.0f), false);
			UE_LOG(LogTemp, Warning, TEXT("Flip Player2P %f"), MoveDir);
		}
	}

}
