// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DMGameUtilities.generated.h"

class ADMPlayer1P;
class ADMPlayer2P;
/**
 * 
 */
UCLASS()
class DEATHMATE_API UDMGameUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DM|Utils")
	static ADMPlayer1P* GetPlayer1P(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "DM|Utils")
	static ADMPlayer2P* GetPlayer2P(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "DM|Utils")
	static void OpenStage(const UObject* WorldContextObject, const int32 StageNum);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "DM|Utils")
	static void OpenStartUI(const UObject* WorldContextObject);
	
};
