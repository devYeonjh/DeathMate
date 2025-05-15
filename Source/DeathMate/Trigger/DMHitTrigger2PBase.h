// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMPaperActorBase.h"
#include "Interface/DMDamagedActor.h"
#include "DMHitTrigger2PBase.generated.h"

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMHitTrigger2PBase : public ADMPaperActorBase, public IDMDamagedActor
{
	GENERATED_BODY()


public:
	void TakeDamage();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Trigger")
	void TriggerEvent();
	
	

};
