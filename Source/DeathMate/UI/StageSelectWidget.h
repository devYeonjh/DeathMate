#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"      // ← Lock 이미지를 쓰려면 추가
#include "StageSelectWidget.generated.h"

UCLASS()
class DEATHMATE_API UStageSelectWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    // 버튼 바인딩
    UPROPERTY(meta = (BindWidget)) UButton* Stage1Button;
    UPROPERTY(meta = (BindWidget)) UButton* Stage2Button;
    UPROPERTY(meta = (BindWidget)) UButton* Stage3Button;

    virtual void NativeConstruct() override;

    UFUNCTION() void OnStage1Clicked();
    UFUNCTION() void OnStage2Clicked();
    UFUNCTION() void OnStage3Clicked();
};
