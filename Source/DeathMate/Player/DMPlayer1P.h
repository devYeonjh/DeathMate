// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DMPlayerBase.h"
#include "InputActionValue.h"
#include "PaperFlipbookActor.h"
#include "Interface/DMDamagedActor.h"
#include "DMPlayer1P.generated.h"

class UInputAction;
class UPaperFlipbook;
/**
 *
 */
UCLASS()
class DEATHMATE_API ADMPlayer1P : public ADMPlayerBase, public IDMDamagedActor
{
	GENERATED_BODY()

public:
	ADMPlayer1P();
	
protected:
	virtual void BeginPlay() override;
	virtual void RespawnAction(const FVector& Checkpoint) override;

private:
	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnPlayer1POverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bIsJumping = false;

public:
	virtual void TakeDamage() override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void TakeDamageBP() { TakeDamage(); }

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetJumpingFinished() { bIsJumping = false; }

	// 데미지 처리 진입점
	UFUNCTION()
	void HandleDamage();

	// 데미지 시퀀스 완료 후 호출될 콜백
	void FinishDeathSequence();

	// 타이머 핸들
	FTimerHandle DeathSequenceHandle;
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	TSubclassOf<APaperFlipbookActor> DeathFlipbookActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UPaperFlipbook* DeathFlipbookAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* JumpSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DieSound;
};
