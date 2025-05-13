// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DMPlayer1P.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "Player/DMSharedController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/DMGameModeBase.h"
#include "Player/DMPlayer2P.h"

ADMPlayer1P::ADMPlayer1P()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player1P"));
	MoveComp->GravityScale = 3.f;
	MoveComp->JumpZVelocity = 1100.f;
	MoveComp->AirControl = 0.5f;
}

void ADMPlayer1P::BeginPlay()
{
	Super::BeginPlay();
	ADMSharedController* PC = Cast<ADMSharedController>(GetWorld()->GetFirstPlayerController());
	DMGM = Cast<ADMGameModeBase>(GetWorld()->GetAuthGameMode());

	//델리게이트 바인딩
	if (PC)
	{
		PC->OnInputMoveTriggered1PAction.AddUObject(this, &ADMPlayer1P::OnInputMoveTriggered);
		PC->OnInputJumpStarted1PAction.AddLambda([this](const FInputActionValue& Value)->void { Jump(); });
		PC->OnInputJumpCompleted1PAction.AddLambda([this](const FInputActionValue& Value)->void { StopJumping(); });
	}
	if (DMGM)
	{
		DMGM->SpawnCheckPointDelegate.AddUObject(this, &ADMPlayer1P::RespawnAction);
	}
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADMPlayer1P::OnPlayer1POverlap);
}


void ADMPlayer1P::OnInputMoveTriggered(const FInputActionValue& Value)
{
	float MoveDirection = Value.Get<float>();


	if (FMath::IsNearlyZero(MoveDirection))
		return;

	AddMovementInput(FVector(MoveDirection, 0.f, 0.f));

	float Yaw = (MoveDirection < 0.f) ? 180.f : 0.f;
	SetActorRotation(FRotator(0.f, Yaw, 0.f));
}

void ADMPlayer1P::OnPlayer1POverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ADMPlayer2P* Player2P = Cast<ADMPlayer2P>(OtherActor);
		if (Player2P)
		{
			DMGM->RespawnAtCheckpoint();
		}
	}
}

void ADMPlayer1P::TakeDamage()
{
	DMGM->RespawnAtCheckpoint();
}

void ADMPlayer1P::RespawnAction(const FVector& Checkpoint)
{
	//TODO : 리스폰 액션 구현
	
	Super::RespawnAction(Checkpoint);
}


