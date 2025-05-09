#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Components/VerticalBox.h"
#include "PauseMenuWidget.generated.h"

class UButton;
class UVerticalBox;
class UImage;

/**
 * 게임 일시정지 메뉴를 처리하는 위젯 클래스
 * A 방법: 위젯 자체에서 키 이벤트 처리
 */
UCLASS()
class DEATHMATE_API UPauseMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // 위젯이 키보드 포커스를 받을 수 있도록 설정
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UImage* PauseBackgroud;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PausePanel;         // 일시정지 메뉴 전체 패널
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ContinueButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;
public:
    UFUNCTION(BlueprintCallable) void ShowPauseMenu();
    UFUNCTION(BlueprintCallable) void ResumeGame();
private:
    bool bPaused = false;
    UFUNCTION()
    void OnContinueClicked();

    UFUNCTION()
    void OnQuitClicked();
};
