// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/DMPlayer1P.h"
#include "Enemy/DMEnemyActor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookActor.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Player/DMSharedController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/DMGameModeBase.h"
#include "Player/DMPlayer2P.h"
#include "PaperZDAnimInstance.h"

ADMPlayer1P::ADMPlayer1P()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player1P"));
	MoveComp->GravityScale = 3.f;
	MoveComp->JumpZVelocity = 1100.f;
	MoveComp->AirControl = 0.5f;
}

void ADMPlayer1P::BeginPlay()
{
	Super::BeginPlay();
	ADMSharedController* PC = Cast<ADMSharedController>(GetWorld()->GetFirstPlayerController());
	DMGM = Cast<ADMGameModeBase>(GetWorld()->GetAuthGameMode());

	//델리게이트 바인딩
	if (PC)
	{
		PC->OnInputMoveStarted1PAction.AddLambda([this](const FInputActionValue& Value)->void { bIsRunning = true; });
		PC->OnInputMoveTriggered1PAction.AddUObject(this, &ADMPlayer1P::OnInputMoveTriggered);
		PC->OnInputMoveCompleted1PAction.AddLambda([this](const FInputActionValue& Value)->void { bIsRunning = false; });

		PC->OnInputJumpStarted1PAction.AddLambda([this](const FInputActionValue& Value)->void 
			{ 
				// 점프 중이 아닐때만 실행
				if (!bIsJumping)
				{
					bIsJumping = true; //점프 중 상태로 변경
					if (JumpSound)
						UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
					GetAnimInstance()->JumpToNode("JumpNode");
					Jump();
				}
			});
		PC->OnInputJumpCompleted1PAction.AddLambda([this](const FInputActionValue& Value)->void { StopJumping(); });
	}
	if (DMGM)
	{
		DMGM->SpawnCheckPointDelegate.AddUObject(this, &ADMPlayer1P::RespawnAction);
	}
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADMPlayer1P::OnPlayer1POverlap);
}


void ADMPlayer1P::OnInputMoveTriggered(const FInputActionValue& Value)
{
	float MoveDirection = Value.Get<float>();


	if (FMath::IsNearlyZero(MoveDirection))
		return;

	AddMovementInput(FVector(MoveDirection, 0.f, 0.f));

	float Yaw = (MoveDirection < 0.f) ? 180.f : 0.f;
	SetActorRotation(FRotator(0.f, Yaw, 0.f));
}

void ADMPlayer1P::OnPlayer1POverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ADMPlayer2P* Player2P = Cast<ADMPlayer2P>(OtherActor);
		if (Player2P)
		{
			HandleDamage();

		}
	}

}

void ADMPlayer1P::TakeDamage()
{
	HandleDamage();
}

void ADMPlayer1P::RespawnAction(const FVector& Checkpoint)
{
	//TODO : 리스폰 액션 구현
	
	Super::RespawnAction(Checkpoint);
}

void ADMPlayer1P::HandleDamage()
{
	//죽은 직후 무적 상태 진입
	if (DieSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DieSound, GetActorLocation());
	}
	SetCanBeDamaged(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 1) 입력 잠그기
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
		PC->DisableInput(PC);

	// 2) 이동 잠그기
	GetCharacterMovement()->SetMovementMode(MOVE_None);

	// 3) 플립북 연출 스폰
	if (DeathFlipbookActorClass && DeathFlipbookAsset)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		APaperFlipbookActor* FB = GetWorld()->SpawnActor<APaperFlipbookActor>(
			DeathFlipbookActorClass,
			GetActorLocation(),
			FRotator::ZeroRotator,
			Params
		);
		if (FB)
		{
			auto* FBComp = FB->GetRenderComponent();
			FBComp->SetFlipbook(DeathFlipbookAsset);
			FBComp->PlayFromStart();
			// 자동 파괴 타이머
			float SeqLen = FBComp->GetFlipbookLength();
			FTimerHandle Tmp;
			GetWorld()->GetTimerManager().SetTimer(Tmp,[FB]() { FB->Destroy(); },SeqLen,false);
		}
	}

	// 4) 숨김
	SetActorHiddenInGame(true);

	// 5) 일정 시간 후 리스폰 콜백
	// FlipbookLength 혹은 임의 Delay
	float DelayTime = 1.5f;  // 원하는 딜레이 시간(초)으로 설정
	GetWorld()->GetTimerManager().SetTimer(DeathSequenceHandle,this,&ADMPlayer1P::FinishDeathSequence,DelayTime,false);
}

void ADMPlayer1P::FinishDeathSequence()
{
	// 1) 리스폰
	if (DMGM)
		DMGM->RespawnAtCheckpoint();

	// 2) 보이기
	SetActorHiddenInGame(false);

	// 3) 이동 복구
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	// 4) 입력 복구
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
		PC->EnableInput(PC);
	//무적 해제
	SetCanBeDamaged(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}