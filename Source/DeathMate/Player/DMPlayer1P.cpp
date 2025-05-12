// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DMPlayer1P.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "Player/DMSharedController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADMPlayer1P::ADMPlayer1P()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player1P"));
	MoveComp->GravityScale = 3.0f;
	MoveComp->JumpZVelocity = 1100.0f;
	MoveComp->AirControl = 0.5f;
}

void ADMPlayer1P::BeginPlay()
{
	Super::BeginPlay();
	ADMSharedController* PC = Cast<ADMSharedController>(GetWorld()->GetFirstPlayerController());

	if (PC)
	{
		PC->OnInputMoveTriggered1PAction.AddUObject(this, &ADMPlayer1P::OnInputMoveTriggered);
		PC->OnInputJumpStarted1PAction.AddLambda([this](const FInputActionValue& Value)->void { Jump(); });
		PC->OnInputJumpCompleted1PAction.AddLambda([this](const FInputActionValue& Value)->void { StopJumping(); });
	}

}


void ADMPlayer1P::OnInputMoveTriggered(const FInputActionValue& Value)
{
	float MoveDirection = Value.Get<float>();


	if (FMath::IsNearlyZero(MoveDirection))
		return;

	AddMovementInput(GetActorForwardVector(), MoveDirection);

	float Yaw = (MoveDirection < 0.f) ? 180.f : 0.f;
	GetSprite()->SetRelativeRotation(FRotator(0.f, Yaw, 0.f));
}


