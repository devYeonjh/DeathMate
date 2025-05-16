// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Player/DMPlayer2P.h"
#include "Utility/DMGameUtilities.h"

void UHpBarWidget::NativeConstruct()
{
    Super::NativeConstruct(); 

	ADMPlayer2P* Player2P = UDMGameUtilities::GetPlayer2P(this);
    Player2P->OnHPChanged.AddUObject(this, &UHpBarWidget::UpdateHPBar);

}

void UHpBarWidget::UpdateHPBar(float NewHpPercent)
{
    if (!HPBar) return;

    HPBar->SetPercent(NewHpPercent);
}
