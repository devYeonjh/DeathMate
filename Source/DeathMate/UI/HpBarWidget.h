#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

class UProgressBar;

UCLASS()
class DEATHMATE_API UHpBarWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HPBar;

private:
    UFUNCTION()
    void UpdateHPBar(float NewHpPercent);
};