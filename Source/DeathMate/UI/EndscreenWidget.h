#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndscreenWidget.generated.h"

class UButton;

/**
 * 메인 로비(StartScreen) 위젯을 C++로 구현한 클래스
 */
UCLASS()
class DEATHMATE_API UEndscreenWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> StartScreenWidgetClass;
protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;
    UFUNCTION()
    void OnExitClicked();
};
