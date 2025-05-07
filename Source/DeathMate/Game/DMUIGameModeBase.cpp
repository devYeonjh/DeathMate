// Fill out your copyright notice in the Description page of Project Settings.
#include "DMUIGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/StageSelectWidget.h"
#include "UI/StartScreenWidget.h"

void ADMUIGameModeBase::BeginPlay()
{
    if (StartScreenWidgetClass)  // UPROPERTY(EditDefaultsOnly) 로 노출
    {
        UUserWidget* StartScreen = CreateWidget<UUserWidget>(GetWorld(), StartScreenWidgetClass);
        if (StartScreen)
        {
            StartScreen->AddToViewport(/*ZOrder=*/ 0);
           
        }
    }
}
