// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMPaperActorBase.h"
#include "DMTrigger2PBase.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMTrigger2PBase : public ADMPaperActorBase
{
	GENERATED_BODY()
	
public:
	ADMTrigger2PBase();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Trigger")
	void TriggerEvent(AActor* OtherActor);
};
