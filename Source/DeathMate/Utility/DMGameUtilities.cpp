// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/DMGameUtilities.h"
#include "DMGameUtilities.h"
#include "Kismet/GameplayStatics.h"
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

void UDMGameUtilities::OpenStage(const UObject* WorldContextObject, const int32 StageNum)
{
	if (WorldContextObject)
	{
		if (StageNum < 1 || StageNum > 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid stage number: %d"), StageNum);
			return;
		}

		UWorld* World = WorldContextObject->GetWorld();
		if (World)
		{
			UGameplayStatics::OpenLevel(World, FName(*FString::Printf(TEXT("stage_%d"), StageNum)));

			ADMPlayer2P* Player2P = GetPlayer2P(WorldContextObject);
			if (Player2P)
			{
				Player2P->OnHPChanged.Clear();
				World->GetTimerManager().ClearAllTimersForObject(Player2P);
			}
			
		}
	}
}

void UDMGameUtilities::OpenStartUI(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	{
		UWorld* World = WorldContextObject->GetWorld();
		if (World)
		{
			UGameplayStatics::OpenLevel(World, TEXT("StartMap"));
			UGameInstance* GI = UGameplayStatics::GetGameInstance(WorldContextObject);
			GI->RemoveLocalPlayer(GI->GetLocalPlayerByIndex(1)); // remove the 2P
		}
	}

}
