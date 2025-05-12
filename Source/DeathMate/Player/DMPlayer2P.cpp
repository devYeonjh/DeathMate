// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayer2P.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/DMSharedController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ADMPlayer2P::ADMPlayer2P()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player2P"));
	MoveComp->GravityScale = 0.0f;
	MoveComp->bUseSeparateBrakingFriction = true;
	MoveComp->BrakingFrictionFactor = 4.0f;
	MoveComp->BrakingFriction = 8.0f;
	MoveComp->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	MoveComp->MaxFlySpeed = 600.0f;
	MoveComp->BrakingDecelerationFlying = 100.0f;
}

void ADMPlayer2P::BeginPlay()
{
	Super::BeginPlay();
	ADMSharedController* PC = Cast<ADMSharedController>(GetWorld()->GetFirstPlayerController());
	if (PC && PC->GetPawn())
	{
		MyCam = PC->GetPawn()->FindComponentByClass<UCameraComponent>();
	}
	if (PC)
	{
		PC->OnInputMoveTriggered2PAction.AddUObject(this, &ADMPlayer2P::OnInputMoveTriggered);
	}

}

void ADMPlayer2P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyCam)
	{
		FVector CamLocation = MyCam->GetComponentLocation();
		FVector CurLocation = GetActorLocation();
		float Width = 1900.0f;
		float Height = 960.0f;
		float MinX = CamLocation.X - Width * 0.5f;
		float MaxX = CamLocation.X + Width * 0.5f;
		float MinZ = CamLocation.Z - Height * 0.5f;
		float MaxZ = CamLocation.Z + Height * 0.5f;
		if (CurLocation.X < MinX)
			CurLocation.X = MinX;
		else if (CurLocation.X > MaxX)
			CurLocation.X = MaxX;
		if (CurLocation.Z < MinZ)
			CurLocation.Z = MinZ;
		else if (CurLocation.Z > MaxZ)
			CurLocation.Z = MaxZ;
		SetActorLocation(CurLocation);
	}
}

void ADMPlayer2P::OnInputMoveTriggered(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>(); // ex) (1,0) (-1, 0) (0, 1) (0, -1)

	FVector ForwardDirection = GetActorForwardVector() * MoveVector.X;
	FVector UpDirection = GetActorUpVector() * MoveVector.Y;
	FVector MoveDirection = ForwardDirection + UpDirection;

	const float Width = 1900.0f;
	const float Height = 960.0f;

	FVector CurLocation = GetActorLocation();
	FVector ScreenCenter = MyCam->GetComponentLocation();

	float MinX = ScreenCenter.X - Width * 0.5f;
	float MaxX = ScreenCenter.X + Width * 0.5f;
	float MinZ = ScreenCenter.Z - Height * 0.5f;
	float MaxZ = ScreenCenter.Z + Height * 0.5f;

	if ((CurLocation.X < MinX && MoveDirection.X < 0) || (CurLocation.X > MaxX && MoveDirection.X > 0))
	{
		MoveDirection.X = 0.0f;
	}
	if ((CurLocation.Z < MinZ && MoveDirection.Z < 0) || (CurLocation.Z > MaxZ && MoveDirection.Z > 0))
	{
		MoveDirection.Z = 0.0f;
	}

	if (MoveDirection.SizeSquared() > 0.0f)
	{
		AddMovementInput(MoveDirection.GetSafeNormal());
	}

	if (MoveDirection.X == 0.0f)
		return;

	float Yaw = (MoveDirection.X < 0.f) ? 0.f : 180.f;
	GetSprite()->SetRelativeRotation(FRotator(0.f, Yaw, 0.f));
}