// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Player/DMPlayer2P.h"
#include "Kismet/GameplayStatics.h"

void UHpBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (ADMPlayer2P* P2 = Cast<ADMPlayer2P>(PC->GetPawn()))
        {
            Player2P = P2;
            Player2P->OnHPChanged.AddUObject(this, &UHpBarWidget::UpdateHPBar);

            UpdateHPBar(Player2P->GetHP());
        }
    }
}

void UHpBarWidget::UpdateHPBar(float NewHP)
{
    if (!HPBar || !Player2P) return;

    // 퍼센트 계산 (0~1)
    const float Percent = NewHP / Player2P->GetMaxHP();
    HPBar->SetPercent(Percent);
}
