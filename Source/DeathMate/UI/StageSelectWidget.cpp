#include "UI/StageSelectWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SaveAndUnlockGame.h"  // �� �������� ���� SaveGame �������Ʈ Ŭ����

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();
    //Ŭ�� �̺�Ʈ ���ε�
    /*if (Stage1Button) Stage1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage1Clicked);
    if (Stage2Button) Stage2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage2Clicked);
    if (Stage3Button) Stage3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage3Clicked);*/

    RefreshStageButtons();
}
void UStageSelectWidget::RefreshStageButtons()
{
    USaveAndUnlockGame* DMStageSave = nullptr;
    int32 UserIndex = 0;

    // 1) ����� �ر� ���� �ҷ�����
    const FString SlotName = TEXT("HighestUnlockedStage");

    if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    {
        // ������ ������ �ε�
        USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
        DMStageSave = Cast<USaveAndUnlockGame>(LoadedGame);
        if (!DMStageSave)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to cast loaded save to USaveAndUnlockGame"));
            // �ʿ��ϴٸ� ���⼭�� ���� �����ϵ��� �б� ó��
        }
    }
    else
    {
        // ������ ������ ���� ���� �� �⺻�� �����ϰ� ����
        DMStageSave = Cast<USaveAndUnlockGame>(
            UGameplayStatics::CreateSaveGameObject(USaveAndUnlockGame::StaticClass())
        );
        if (DMStageSave)
        {
            DMStageSave->HighestUnlockedStage = 1;  // �ʱ� �ر� ��������
            const bool bSaved = UGameplayStatics::SaveGameToSlot(DMStageSave, SlotName, UserIndex);
            UE_LOG(LogTemp, Log, TEXT("Created new save slot '%s', success: %s"),
                *SlotName, bSaved ? TEXT("true") : TEXT("false"));
        }
    }

    // �� 2) ��ư Ȱ��ȭ ����
    if (DMStageSave)
    {
        const int32 Highest = DMStageSave->HighestUnlockedStage;
        if (Stage1Button) Stage1Button->SetIsEnabled(true);
        if (Stage2Button) Stage2Button->SetIsEnabled(Highest >= 2);
        if (Stage3Button) Stage3Button->SetIsEnabled(Highest >= 3);
    }
}

void UStageSelectWidget::OnStage1Clicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/stage_01"));
}

void UStageSelectWidget::OnStage2Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/stage_02"));
}

void UStageSelectWidget::OnStage3Clicked()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Maps/stage_03"));
}
