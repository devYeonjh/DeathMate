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

public:
    // 블루프린트나 C++에서 마음대로 호출할 수 있게!
    UFUNCTION(BlueprintCallable, Category = "StageSelect")
    void RefreshStageButtons();
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
