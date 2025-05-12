#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"        // ← 버튼을 쓰려면 추가
#include "StageSelectWidget.generated.h"

UCLASS()
class DEATHMATE_API UStageSelectWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* Stage1Button;
    UPROPERTY(meta = (BindWidget))
    UButton* Stage2Button;
    UPROPERTY(meta = (BindWidget))
    UButton* Stage3Button;

    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnStage1Clicked();
    UFUNCTION()
    void OnStage2Clicked();
    UFUNCTION()
    void OnStage3Clicked();
};
