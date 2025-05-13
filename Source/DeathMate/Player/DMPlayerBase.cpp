// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayerBase.h"
#include "UObject/ConstructorHelpers.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ADMPlayerBase::ADMPlayerBase()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Game/Input/IMC_PlayerController.IMC_PlayerController"));
	if (IMCObj.Succeeded())
	{
		IMC_PlayerInput = IMCObj.Object;
	}

	MoveComp = GetCharacterMovement();
	
	MoveComp->SetPlaneConstraintEnabled(true);
	MoveComp->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Custom);
	MoveComp->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
	bUseControllerRotationYaw = false;
}

void ADMPlayerBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (SubSystem && IMC_PlayerInput)
		{
			SubSystem->AddMappingContext(IMC_PlayerInput, 0);
		}
	}
}

void ADMPlayerBase::RespawnAction(const FVector& Checkpoint)
{
	SetActorLocation(Checkpoint);
}
