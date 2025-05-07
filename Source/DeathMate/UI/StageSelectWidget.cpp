// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StageSelectWidget.h"
#include "StageSelectWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UStageSelectWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // UMG���� BindWidget�� Stage1Button�� ��ȿ�ϸ�, OnClicked ��������Ʈ�� �Լ� ���ε�
    if (Stage1Button)
    {
        Stage1Button->OnClicked.AddDynamic(this, &UStageSelectWidget::OnStage1Clicked);
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
        FName("Map_2D1"),                      // �ε��� �� �̸�
        /*bAbsolute=*/ true,
        FString("Game=/Game/Blueprints/BP_DMGameModeBase.BP_DMGameModeBase_C")
    );
}
