// Fill out your copyright notice in the Description page of Project Settings.
#include "DMUIGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/StageSelectWidget.h"
#include "UI/StartScreenWidget.h"
#include "GameFramework/PlayerController.h"
void ADMUIGameModeBase::BeginPlay()
{
    if (StartScreenWidgetClass)  // UPROPERTY(EditDefaultsOnly) 로 노출
    {
        UUserWidget* StartScreen = CreateWidget<UUserWidget>(GetWorld(), StartScreenWidgetClass);
        if (StartScreen)
        {
            StartScreen->AddToViewport(/*ZOrder=*/ 0);
            if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
            {
                PC->bShowMouseCursor = true;
                PC->bEnableClickEvents = true;
                PC->bEnableMouseOverEvents = true;

                FInputModeUIOnly UIInput;
                UIInput.SetWidgetToFocus(StartScreen->TakeWidget());
                UIInput.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(UIInput);
            }
        }
    }
}
