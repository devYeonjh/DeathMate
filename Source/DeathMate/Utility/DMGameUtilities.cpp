// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/DMGameUtilities.h"
#include "DMGameUtilities.h"
#include "Player/DMPlayer1P.h"
#include "Player/DMPlayer2P.h"
#include "EngineUtils.h"


ADMPlayer1P* UDMGameUtilities::GetPlayer1P(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = WorldContextObject->GetWorld();
		if (World)
		{
			for (TActorIterator<ADMPlayer1P> It(World); It; ++It)
			{
				return *It;
			}
		}
	}	
	return nullptr;
}

ADMPlayer2P* UDMGameUtilities::GetPlayer2P(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = WorldContextObject->GetWorld();
		if (World)
		{
			for (TActorIterator<ADMPlayer2P> It(World); It; ++It)
			{
				return *It;
			}
		}
	}
	return nullptr;
}
