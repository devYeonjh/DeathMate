// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DMInputComponent.generated.h"


UCLASS( ClassGroup=(Input), meta=(BlueprintSpawnableComponent) )
class DEATHMATE_API UDMInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDMInputComponent();

private:
	//========================Input Action========================
	//할당된 IA가 없을 시 Action binding을 하지 않음
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* IMC_PlayerInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction", meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction", meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction", meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Dash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InputAction", meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Attack;

private:
	//==========================Flipbook==========================
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Idle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Run;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Fall;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Dash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Attack;

		
};
