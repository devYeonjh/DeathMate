// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StageSelectWidget.h"
#include "StageSelectWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // UMG에서 BindWidget한 Stage1Button이 유효하면, OnClicked 델리게이트에 함수 바인딩
    if (Stage1Button && Stage2Button && Stage3Button)
    {
        Stage1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage1Clicked);
        Stage2Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage2Clicked);
        Stage3Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage3Clicked);
    }
}

void UStageSelectWidget::OnStage1Clicked()
{
    RemoveFromParent();
    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
    UGameplayStatics::OpenLevel(
        GetWorld(),                            // WorldContextObject
        FName("stage_1"),                      // 로드할 맵 이름
        /*bAbsolute=*/ true,
        FString("Game=/Game/Blueprints/BP_DMGameModeBase.BP_DMGameModeBase_C")
    );
}

void UStageSelectWidget::OnStage2Clicked()
{
    RemoveFromParent();
    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
    UGameplayStatics::OpenLevel(
        GetWorld(),                            // WorldContextObject
        FName("stage_2"),                      // 로드할 맵 이름
        /*bAbsolute=*/ true,
        FString("Game=/Game/Blueprints/BP_DMGameModeBase.BP_DMGameModeBase_C")
    );
}

void UStageSelectWidget::OnStage3Clicked()
{
    RemoveFromParent();
    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
    UGameplayStatics::OpenLevel(
        GetWorld(),                            // WorldContextObject
        FName("stage_3"),                      // 로드할 맵 이름
        /*bAbsolute=*/ true,
        FString("Game=/Game/Blueprints/BP_DMGameModeBase.BP_DMGameModeBase_C")
    );
}