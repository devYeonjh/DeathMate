// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMSharedController.h"
#include "Player/DMPaperCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "GameFramework/CharacterMovementComponent.h"


ADMSharedController::ADMSharedController()
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

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PFDashObj(TEXT("/Game/PaperAsset/Character/Character2P/FlipBooks/grim_reaper_dash.grim_reaper_dash"));
	if (PFDashObj.Succeeded())
	{
		PF_Idle = PFDashObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PFIdleObj(TEXT("/Game/PaperAsset/Character/Character2P/FlipBooks/grim_reaper_idle.grim_reaper_idle"));
	if (PFIdleObj.Succeeded())
	{
		PF_Dash = PFIdleObj.Object;
	}
}

void ADMSharedController::SetPlayer2P(ADMPaperCharacter* const NewPlayer2P)
{
	ensure(NewPlayer2P);
	Player2P = NewPlayer2P;
}

void ADMSharedController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent && IA_DMMove2P)
	{
		EnhancedInputComponent->BindAction(IA_DMMove2P, ETriggerEvent::Triggered, this, &ADMSharedController::OnInputMoveTriggered);
		EnhancedInputComponent->BindAction(IA_Dash2P, ETriggerEvent::Completed, this, &ADMSharedController::OnInputDash);
	}
}



void ADMSharedController::OnInputMoveTriggered(const FInputActionValue& Value)
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

void ADMSharedController::OnInputDash(const FInputActionValue& Value)
{
	if (Player2P)
	{
		if (PF_Dash && Player2P->GetSprite()->GetFlipbook() != PF_Dash)
		{
			Player2P->GetSprite()->SetFlipbook(PF_Dash);
			Player2P->GetSprite()->Play();
		}
		UE_LOG(LogTemp, Warning, TEXT("Dash"));
	}

}
