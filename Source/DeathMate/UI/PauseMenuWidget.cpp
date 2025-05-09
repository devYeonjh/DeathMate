#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 키보드 포커스 설정
    this->SetKeyboardFocus();

    // 버튼 바인딩
    if (ContinueButton)
        ContinueButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnContinueClicked);
    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitClicked);
}

void UPauseMenuWidget::ShowPauseMenu()
{
    bPaused = true;
    PausePanel->SetVisibility(ESlateVisibility::Visible);
    PauseBackgroud->SetVisibility(ESlateVisibility::Visible);

    if (auto* PC = GetOwningPlayer< APlayerController >())
    {
        PC->SetPause(true);
        PC->bShowMouseCursor = true;
        FInputModeUIOnly Mode;
        Mode.SetWidgetToFocus(PausePanel->TakeWidget());
        PC->SetInputMode(Mode);
    }
}

void UPauseMenuWidget::ResumeGame()
{
    bPaused = false;
    PausePanel->SetVisibility(ESlateVisibility::Hidden);
    PauseBackgroud->SetVisibility(ESlateVisibility::Hidden);
    if (auto* PC = GetOwningPlayer< APlayerController >())
    {
        PC->SetPause(false);
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
}

void UPauseMenuWidget::OnContinueClicked()
{
    ResumeGame();
}

void UPauseMenuWidget::OnQuitClicked()
{
    // StartUI 맵으로 돌아가기
    UGameplayStatics::OpenLevel(this, TEXT("StartUI"));
}