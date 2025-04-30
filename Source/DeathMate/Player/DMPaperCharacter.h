// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "DMPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ADMPaperCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	int32 PlayerIndex = -1;

	class UInputMappingContext* IMC_DMPlayerInput;
	class UInputAction* IA_DMMove1P;
	class UInputAction* IA_Jump1P;

private:
	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Idle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Run;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Jump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flipbook", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbook* PF_Fall;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	FORCEINLINE int32 GetPlayerIndex() const { return PlayerIndex; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	FORCEINLINE void SetPlayerIndex(int32 NewIndex) { PlayerIndex = NewIndex; }

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

private:
	void BindInputActions(class UEnhancedInputComponent* EnhancedInputComponent);

	void OnInputMoveStarted(const FInputActionValue& Value);
	void OnInputMoveTriggered(const FInputActionValue& Value);
	void OnInputMoveCompleted(const FInputActionValue& Value);

	void OnInputJumpStarted(const FInputActionValue& Value);
	void OnInputJumpCompleted(const FInputActionValue& Value);

	void HandlePlayerSpecificPossession();
};
