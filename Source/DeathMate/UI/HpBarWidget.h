// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

class UProgressBar;
class ADMPlayer2P;
/**
 * 
 */
UCLASS()
class DEATHMATE_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

private:
	UPROPERTY()
	ADMPlayer2P* Player2P;

	UFUNCTION()
	void UpdateHPBar(float NewHP);
	
};
