// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPaperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/DMSharedController.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADMPaperCharacter::ADMPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Game/Input/IMC_PlayerController.IMC_PlayerController"));
	if (IMCObj.Succeeded())
	{
		IMC_DMPlayerInput = IMCObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IAObj(TEXT("/Game/Input/Action/IA_Move.IA_Move"));
	if (IAObj.Succeeded())
	{
		IA_DMMove1P = IAObj.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IAJumpObj(TEXT("/Game/Input/Action/IA_Jump.IA_Jump"));
	if (IAJumpObj.Succeeded())
	{
		IA_Jump1P = IAJumpObj.Object;
	}

	MySprite = GetSprite();

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->SetPlaneConstraintEnabled(true);
	MoveComp->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Custom);
	MoveComp->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
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
	if (PlayerIndex == 0)
	{
		EnhancedInputComponent->BindAction(IA_DMMove1P, ETriggerEvent::Triggered, this, &ADMPaperCharacter::OnInputMoveTriggered);

		EnhancedInputComponent->BindAction(IA_Jump1P, ETriggerEvent::Started, this, &ADMPaperCharacter::OnInputJumpStarted);
		EnhancedInputComponent->BindAction(IA_Jump1P, ETriggerEvent::Completed, this, &ADMPaperCharacter::OnInputJumpCompleted);
	}
}


void ADMPaperCharacter::OnInputMoveTriggered(const FInputActionValue& Value)
{
	float MoveDirection = Value.Get<float>();

	if (PF_Run && GetMovementComponent()->IsMovingOnGround() && MySprite->GetFlipbook() != PF_Run)
	{
		MySprite->SetFlipbook(PF_Run);
		MySprite->Play();
	}

	if (FMath::IsNearlyZero(MoveDirection))
		return;

	AddMovementInput(GetActorForwardVector(), MoveDirection);

	float Yaw = (MoveDirection < 0.f) ? 180.f : 0.f;
	MySprite->SetRelativeRotation(FRotator(0.f, Yaw, 0.f));
}

void ADMPaperCharacter::OnInputMoveCompleted(const FInputActionValue& Value)
{
	if (PF_Idle && MySprite->GetFlipbook() != PF_Idle)
	{
		MySprite->SetFlipbook(PF_Idle);
		MySprite->Play();
	}
}

void ADMPaperCharacter::OnInputJumpStarted(const FInputActionValue& Value)
{
	Jump();
}

void ADMPaperCharacter::OnInputJumpCompleted(const FInputActionValue& Value)
{
	StopJumping();
}


void ADMPaperCharacter::HandlePlayerSpecificPossession()
{
	if (PlayerIndex == 1)
	{
		ADMSharedController* DMSharedController = Cast<ADMSharedController>(GetWorld()->GetFirstPlayerController());
		if (DMSharedController)
		{
			DMSharedController->SetPlayer2P(this);
		}
	}
}