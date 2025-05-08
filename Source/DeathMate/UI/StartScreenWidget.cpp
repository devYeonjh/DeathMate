#include "StartScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UStartScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UStartScreenWidget::OnStartClicked);
    }
    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UStartScreenWidget::OnQuitClicked);
    }
}

void UStartScreenWidget::OnStartClicked()
{
    // 1) 이 위젯(self)을 화면에서 제거
    RemoveFromParent();

    // 2) 마우스 커서 보이기 및 입력 모드 UI Only 로 변경
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        PC->bShowMouseCursor = true;
        FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);
    }

    // 3) StageSelectWidgetClass로 위젯 생성 후 화면에 추가
    if (StageSelectWidgetClass)
    {
        UUserWidget* StageSelect = CreateWidget<UUserWidget>(GetWorld(), StageSelectWidgetClass);
        if (StageSelect)
        {
            StageSelect->AddToViewport(/*ZOrder=*/ 1);
        }
    }
}

void UStartScreenWidget::OnQuitClicked()
{
    // 게임 종료
    UKismetSystemLibrary::QuitGame(this,
        UGameplayStatics::GetPlayerController(this, 0),
        EQuitPreference::Quit,
        /*bIgnorePlatformRestrictions=*/ true);
}
