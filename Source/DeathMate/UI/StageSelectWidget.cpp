#include "UI/StageSelectWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SaveAndUnlockGame.h"  // ← 여러분이 만든 SaveGame 블루프린트 클래스

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();
    //클릭 이벤트 바인딩
    if (Stage1Button) Stage1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage1Clicked);
    if (Stage2Button) Stage2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage2Clicked);
    if (Stage3Button) Stage3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage3Clicked);

    RefreshStageButtons();
}
void UStageSelectWidget::RefreshStageButtons()
{
    // 1) 저장된 해금 정보 불러오기
    const FString SlotName = TEXT("HighestUnlockedStage");
    USaveAndUnlockGame* DMStageSave = Cast<USaveAndUnlockGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
    if (!DMStageSave)
    {
        // 없으면 기본값(1)으로 새로 생성 후 저장
        DMStageSave = Cast<USaveAndUnlockGame>(UGameplayStatics::CreateSaveGameObject(USaveAndUnlockGame::StaticClass()));
        UGameplayStatics::SaveGameToSlot(DMStageSave, SlotName, 0);
    }

    int32 Highest = DMStageSave->HighestUnlockedStage;  // 몇 번째 스테이지까지 열려 있는지
    if (Stage1Button) Stage1Button->SetIsEnabled(true);
    if (Stage2Button) Stage2Button->SetIsEnabled(Highest >= 2);
    if (Stage3Button) Stage3Button->SetIsEnabled(Highest >= 3);
}

void UStageSelectWidget::OnStage1Clicked()
{
    // ... (기존에 쓰시던 OpenLevel 코드)
    UGameplayStatics::OpenLevel(GetWorld(), FName("stage_1"));
}

void UStageSelectWidget::OnStage2Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("stage_2"));
}

void UStageSelectWidget::OnStage3Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("stage_3"));
}
