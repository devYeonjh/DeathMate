#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartScreenWidget.generated.h"

class UButton;

/**
 * 메인 로비(StartScreen) 위젯을 C++로 구현한 클래스
 */
UCLASS()
class DEATHMATE_API UStartScreenWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // 에디터(C++) 또는 블루프린트에서 설정할 스테이지 선택 위젯 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> StageSelectWidgetClass;

protected:
    virtual void NativeConstruct() override;

    // UMG 디자이너에서 BindWidget 될 버튼들
    UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

    // 버튼 클릭 시 호출될 함수
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnQuitClicked();
};
