// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DMSharedController.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMSharedController : public APlayerController
{
	GENERATED_BODY()

public:
	ADMSharedController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	class ADMPaperCharacter* Player2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_DMMove2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_Dash2P;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* IA_Attack2P;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetPlayer2P(class ADMPaperCharacter* const NewPlayer2P);

protected:
	virtual void SetupInputComponent() override;

	bool bHasFiredAttackNotify;

	UFUNCTION()
	void OnFlipbookPlaybackPositionChanged(UPaperFlipbookComponent* FlipbookComp);

	void PerformAttack();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Idle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Dash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Attack;

	class UCameraComponent* MyCam;

private:
	void OnInputMoveTriggered(const FInputActionValue& Value);

	void OnInputDash(const FInputActionValue& Value);

	void OnInputAttack(const FInputActionValue& Value);


	
};
