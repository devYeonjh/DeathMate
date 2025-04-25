// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/DMPlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"

ADMPaperCharacter::ADMPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Game/DoHoon/Input/IMC_PlayerController.IMC_PlayerController"));
	if (IMCObj.Succeeded())
	{
		IMC_DMPlayerInput = IMCObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAObj(TEXT("/Game/DoHoon/Input/Action/IA_Move.IA_Move"));
	if (IAObj.Succeeded())
	{
		IA_DMMove1P = IAObj.Object;
	}

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->MaxSpeed = 500.0f;		
	PawnMovement->Acceleration = 2048.0f;	
	PawnMovement->Deceleration = 2000.0f;	
	PawnMovement->TurningBoost = 8.0f;		
}

void ADMPaperCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (SubSystem && IMC_DMPlayerInput)
		{
			SubSystem->AddMappingContext(IMC_DMPlayerInput, 0);
			UE_LOG(LogTemp, Warning, TEXT("Added Input Mapping Context for Player %d"), GetPlayerIndex());
		}
	}
}

void ADMPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		BindInputActions(EnhancedInputComponent);
	}
	HandlePlayerSpecificPossession();
}

void ADMPaperCharacter::BindInputActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (PlayerIndex == 0 && IA_DMMove1P)
	{
		EnhancedInputComponent->BindAction(IA_DMMove1P, ETriggerEvent::Triggered, this, &ADMPaperCharacter::OnInputMove);
	}
}

void ADMPaperCharacter::OnInputMove(const FInputActionValue& Value)
{
	float MoveDirection = Value.Get<float>(); // ex) (1,0) (-1, 0) (0, 1) (0, -1)

	FVector ForwardDirection = GetActorForwardVector() * MoveDirection;

	if (ForwardDirection.SizeSquared() > 0.0f)
	{
		AddMovementInput(ForwardDirection.GetSafeNormal());
	}
}

void ADMPaperCharacter::HandlePlayerSpecificPossession()
{
	if (PlayerIndex == 1)
	{
		ADMPlayerController* DMPlayerController = Cast<ADMPlayerController>(GetWorld()->GetFirstPlayerController());
		if (DMPlayerController)
		{
			DMPlayerController->SetPlayer2P(this);
		}

	}
}