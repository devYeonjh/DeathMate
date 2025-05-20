#include "EndscreenWidget.h"
#include "StageSelectWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UEndscreenWidget::NativeConstruct()
{
    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->bShowMouseCursor = true;


        FInputModeUIOnly InputMode;

        InputMode.SetWidgetToFocus(this->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

        PC->SetInputMode(InputMode);
    }
    Super::NativeConstruct();
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UEndscreenWidget::OnExitClicked);
    }
}

void UEndscreenWidget::OnExitClicked()
{
    RemoveFromParent();

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        PC->bShowMouseCursor = true;
        FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PC->SetInputMode(InputMode);
    }
    if (StartScreenWidgetClass)
    {
        UUserWidget* StartStage = CreateWidget<UUserWidget>(GetWorld(), StartScreenWidgetClass);
        if (StartStage)
        {
            StartStage->AddToViewport(/*ZOrder=*/ 1);
        }
    }
}
