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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* IMC_DMPlayerInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* IA_DMMove1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UFloatingPawnMovement* PawnMovement;

public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	FORCEINLINE int32 GetPlayerIndex() const { return PlayerIndex; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	FORCEINLINE void SetPlayerIndex(int32 NewIndex) { PlayerIndex = NewIndex; }

protected:

	// 플레이어 컨트롤러에 의해 Possessed 될 때 호출
	virtual void PossessedBy(AController* NewController) override;
	// 입력 컨트롤러 설정
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 입력 바인딩을 할 함수
	void BindInputActions(class UEnhancedInputComponent* EnhancedInputComponent);

	// 입력 이동 처리 함수
	void OnInputMove(const FInputActionValue& Value);


	void HandlePlayerSpecificPossession();

	
};
