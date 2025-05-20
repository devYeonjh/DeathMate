
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"          // ← UUserWidget 쓰려면 꼭 필요합니다
#include "UI/StartScreenWidget.h"         // ← StartScreenWidget 클래스를 쓰려면
#include "DMUIGameModeBase.generated.h"   // ← 항상 다른 include 뒤, 클래스 선언 바로 직전!

UCLASS()
class DEATHMATE_API ADMUIGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
protected:
    // 여기 StartScreenWidgetClass가 정의되어 있어야
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UStartScreenWidget> StartScreenWidgetClass;

private:
    // 인스턴스 보관용
    UPROPERTY()
    UStartScreenWidget* StartScreenWidgetInstance;
};