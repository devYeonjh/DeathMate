#include "UI/StageSelectWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SaveAndUnlockGame.h"  // ← 여러분이 만든 SaveGame 블루프린트 클래스

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();
    //클릭 이벤트 바인딩
    /*if (Stage1Button) Stage1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage1Clicked);
    if (Stage2Button) Stage2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage2Clicked);
    if (Stage3Button) Stage3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage3Clicked);*/

    RefreshStageButtons();
}
void UStageSelectWidget::RefreshStageButtons()
{
    USaveAndUnlockGame* DMStageSave = nullptr;
    int32 UserIndex = 0;

    // 1) 저장된 해금 정보 불러오기
    const FString SlotName = TEXT("HighestUnlockedStage");

    if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    {
        // 파일이 있으면 로드
        USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
        DMStageSave = Cast<USaveAndUnlockGame>(LoadedGame);
        if (!DMStageSave)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to cast loaded save to USaveAndUnlockGame"));
            // 필요하다면 여기서도 새로 생성하도록 분기 처리
        }
    }
    else
    {
        // 파일이 없으면 새로 생성 후 기본값 세팅하고 저장
        DMStageSave = Cast<USaveAndUnlockGame>(
            UGameplayStatics::CreateSaveGameObject(USaveAndUnlockGame::StaticClass())
        );
        if (DMStageSave)
        {
            DMStageSave->HighestUnlockedStage = 1;  // 초기 해금 스테이지
            const bool bSaved = UGameplayStatics::SaveGameToSlot(DMStageSave, SlotName, UserIndex);
            UE_LOG(LogTemp, Log, TEXT("Created new save slot '%s', success: %s"),
                *SlotName, bSaved ? TEXT("true") : TEXT("false"));
        }
    }

    // ▷ 2) 버튼 활성화 로직
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
