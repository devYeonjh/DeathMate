// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/DMPlayerBase.h"
#include "InputActionValue.h"
#include "DMPlayer2P.generated.h"

class UInputAction;
class UPaperFlipbook;
class APaperFlipbookActor;
class ADMFollowingCamera;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPChangedDyn, float, NewHP);

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMPlayer2P : public ADMPlayerBase
{
	GENERATED_BODY()


public:
	ADMPlayer2P();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void RespawnAction(const FVector& Checkpoint) override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

private:
	ADMFollowingCamera* MyCam;
	UWorld* MyWorld;
	const FVector LocalOffset = FVector(-40.f, 0.f, 0.f);
	const FVector BoxExtent = FVector(50.f, 30.f, 40.f);

	UFUNCTION()
	void OnInputMoveTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void SetHPTimer() { SetHP(CurrentHP - DamagePerTick); }

private:
	bool bIsAttacking = false;
	bool bSkipClamp = false;


public:
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetAttackFinished() { bIsAttacking = false; }

	UFUNCTION(BlueprintCallable, Category = "Player")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void GetSpirit(float Amount) { SetHP(CurrentHP + Amount); }
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat|VFX")
	TSubclassOf<APaperFlipbookActor> AttackFlipbookActorClass;
	UPROPERTY(EditDefaultsOnly, Category = "Combat|VFX")
	UPaperFlipbook* AttackFlipbookAsset;


private:
	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxHP = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentHP;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float HPDecreaseInterval = 1.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float DamagePerTick = 1.f;

	FTimerHandle HPTimerHandle;
public:
	void SetHP(float NewHealth);
	FORCEINLINE float GetHP() const { return CurrentHP; }
	FORCEINLINE float GetMaxHP() const { return MaxHP; }

	//FOnHPChangedDelegate OnHPChanged;
	FOnHPChangedDyn OnHPChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* AttackSound;

};
