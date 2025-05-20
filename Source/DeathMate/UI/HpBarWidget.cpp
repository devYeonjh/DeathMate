// HpBarWidget.cpp
#include "UI/HpBarWidget.h"
#include "Player/DMPlayer2P.h"
#include "Utility/DMGameUtilities.h"
#include "Components/ProgressBar.h"


void UHpBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 플레이어 2P의 OnHPChanged 델리게이트에 바인딩
    if (ADMPlayer2P* Player2P = UDMGameUtilities::GetPlayer2P(this))
    {
        Player2P->OnHPChanged.AddUObject(this, &UHpBarWidget::UpdateHPBar);
    }
}

void UHpBarWidget::UpdateHPBar(float NewHpPercent)
{
    if (!HPBar)
        return;
	// HPBar의 목표치 설정
    HPBar->SetPercent(NewHpPercent);
}
