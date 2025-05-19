#include "UI/StageSelectWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SaveAndUnlockGame.h"  // �� �������� ���� SaveGame �������Ʈ Ŭ����

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 1) ����� �ر� ���� �ҷ�����
    const FString SlotName = TEXT("SaveAndUnlockGame");
    USaveAndUnlockGame* DMStageSave = Cast<USaveAndUnlockGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
    if (!DMStageSave)
    {
        // ������ �⺻��(1)���� ���� ���� �� ����
        DMStageSave = Cast<USaveAndUnlockGame>(UGameplayStatics::CreateSaveGameObject(USaveAndUnlockGame::StaticClass()));
        UGameplayStatics::SaveGameToSlot(DMStageSave, SlotName, 0);
    }

    int32 Highest = DMStageSave->HighestUnlockedStage;  // �� ��° ������������ ���� �ִ���

    // 2) ��ư ���/�ر� & Lock �̹��� ���
    Stage1Button->SetIsEnabled(true);                // ��������1�� �׻� Ȱ��
    Stage2Button->SetIsEnabled(Highest >= 2);
    Stage3Button->SetIsEnabled(Highest >= 3);

    // 3) Ŭ�� �̺�Ʈ ���ε�
    if (Stage1Button) Stage1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage1Clicked);
    if (Stage2Button) Stage2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage2Clicked);
    if (Stage3Button) Stage3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage3Clicked);
}

void UStageSelectWidget::OnStage1Clicked()
{
    // ... (������ ���ô� OpenLevel �ڵ�)
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
