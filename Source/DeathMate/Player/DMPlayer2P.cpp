// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayer2P.h"
#include "DMPlayer1P.h"
#include "Trigger/DMTrigger2PBase.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "Player/DMSharedController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperZDAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Game/DMGameModeBase.h"
#include "Player/DMFollowingCamera.h"
#include "Engine/OverlapResult.h"
#include "Interface/DMDamagedActor.h"
#include "Game/DMGameModeBase.h"
#include "Components/CapsuleComponent.h"



ADMPlayer2P::ADMPlayer2P()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player2P"));
	
	//2P 기본 설정(공중 이동)
	MoveComp->GravityScale = 0.f;
	MoveComp->bUseSeparateBrakingFriction = true;
	MoveComp->BrakingFrictionFactor = 4.f;
	MoveComp->BrakingFriction = 8.f;
	MoveComp->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	MoveComp->MaxFlySpeed = 600.f;
	MoveComp->BrakingDecelerationFlying = 100.f;
}

void ADMPlayer2P::BeginPlay()
{
	Super::BeginPlay();
	
	if (AGameModeBase* GM = GetWorld()->GetAuthGameMode())
	{
		ADMGameModeBase* DMGM = Cast<ADMGameModeBase>(GM);
		if (DMGM)
		{
			MyCam = DMGM->GetMainCamera();
			DMGM->SpawnCheckPointDelegate.AddUObject(this, &ADMPlayer2P::RespawnAction);
		}
	}
	
	ADMSharedController* PC = Cast<ADMSharedController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->OnInputMoveStarted2PAction.AddLambda([this](const FInputActionValue&)->void { bIsRunning = true; });
		PC->OnInputMoveTriggered2PAction.AddUObject(this, &ADMPlayer2P::OnInputMoveTriggered);
		PC->OnInputMoveCompleted2PAction.AddLambda([this](const FInputActionValue&)->void { bIsRunning = false; });

		PC->OnInputAttackStarted2PAction.AddLambda([this](const FInputActionValue&)->void {
			if (!bIsAttacking)
			{
				GetAnimInstance()->JumpToNode("AttackJump");
				bIsAttacking = true;
			}
		});
	}	
}

//카메라 크기에 맞게이동 제한
void ADMPlayer2P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSkipClamp)
	{
		bSkipClamp = false;
		return;
	}

	FVector CamLocation = MyCam->GetActorLocation();
	FVector CurLoc = GetActorLocation();
	FVector TargetLoc = CurLoc;
	bool bNeedClamp = false;

	float MinX = CamLocation.X - MyCam->GetCameraHalfWidth();
	float MaxX = CamLocation.X + MyCam->GetCameraHalfWidth();
	float MinZ = CamLocation.Z - MyCam->GetCameraHalfHeight();
	float MaxZ = CamLocation.Z + MyCam->GetCameraHalfHeight();
		
	if (TargetLoc.X < MinX) { TargetLoc.X = MinX; bNeedClamp = true; }
	else if (TargetLoc.X > MaxX) { TargetLoc.X = MaxX; bNeedClamp = true; }
	if (TargetLoc.Z < MinZ) { TargetLoc.Z = MinZ; bNeedClamp = true; }
	else if (TargetLoc.Z > MaxZ) { TargetLoc.Z = MaxZ; bNeedClamp = true; }

	if (bNeedClamp)
	{
		FHitResult Hit;
		FCollisionQueryParams Params(NAME_None, /*bTraceComplex=*/false, this);

		bool bBlocked = GetWorld()->SweepSingleByChannel(
				Hit,
				CurLoc,
				TargetLoc,
				FQuat::Identity,
				ECC_WorldStatic,
				FCollisionShape::MakeCapsule(
				GetCapsuleComponent()->GetScaledCapsuleRadius(),
				GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
			),
			/*Params*/       Params
		);

		if (bBlocked)
		{
			// 지형에 박힌 걸 감지하면 체크포인트로 리스폰
			if (auto* GM = Cast<ADMGameModeBase>(GetWorld()->GetAuthGameMode()))
			{
				GM->RespawnAtCheckpoint();  // GameMode에서 브로드캐스트 → ADMPlayer2P::RespawnAction 호출 :contentReference[oaicite:0]{index=0}:contentReference[oaicite:1]{index=1}
			}
			return;
		}
	}
	SetActorLocation(TargetLoc);
}

void ADMPlayer2P::RespawnAction(const FVector& Checkpoint)
{
	//TODO : 리스폰 액션 구현
	FVector Player2POffset = FVector(-200.f, 0.f, 100.f);
	Super::RespawnAction(Checkpoint + Player2POffset);
	bSkipClamp = true;
}

void ADMPlayer2P::OnInputMoveTriggered(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>(); // ex) (1,0) (-1, 0) (0, 1) (0, -1)

	FVector MoveDirection = FVector(MoveVector.X, 0.f, MoveVector.Y);

	FVector CamLocation = MyCam->GetActorLocation();
	FVector CurLocation = GetActorLocation();

	float MinX = CamLocation.X - MyCam->GetCameraHalfWidth();
	float MaxX = CamLocation.X + MyCam->GetCameraHalfWidth();
	float MinZ = CamLocation.Z - MyCam->GetCameraHalfHeight();
	float MaxZ = CamLocation.Z + MyCam->GetCameraHalfHeight();

	if ((CurLocation.X < MinX && MoveDirection.X < 0) || (CurLocation.X > MaxX && MoveDirection.X > 0))
	{
		MoveDirection.X = 0.f;
	}
	if ((CurLocation.Z < MinZ && MoveDirection.Z < 0) || (CurLocation.Z > MaxZ && MoveDirection.Z > 0))
	{
		MoveDirection.Z = 0.f;
	}

	if (MoveDirection.SizeSquared() > 0.f)
	{
		AddMovementInput(MoveDirection.GetSafeNormal());
	}

	if (MoveDirection.X == 0.f)
		return;

	float Yaw = (MoveDirection.X < 0.f) ? 0.f : 180.f;

	SetActorRotation(FRotator(0.f, Yaw, 0.f));
}

void ADMPlayer2P::Attack()
{
	UWorld* World = GetWorld();
	if (!World) return;

	const FVector LocalOffset(-40.f, 0.f, 0.f);
	const FVector Center = GetActorLocation() + GetActorRotation().RotateVector(LocalOffset);

	const FVector BoxExtent(50.f, 30.f, 20.f);

	TArray<FOverlapResult> Results;
	bool bHit = GetWorld()->OverlapMultiByProfile(
		Results,
		Center,
		GetActorRotation().Quaternion(),
		TEXT("Player2PAttack"),
		FCollisionShape::MakeBox(BoxExtent)
	);

	for (const FOverlapResult& Result : Results)
	{
		if (ADMTrigger2PBase* Switch = Cast<ADMTrigger2PBase>(Result.GetActor()))
		{
			Switch->TriggerEvent(Result.GetActor());
		}

		AActor* HitActor = Result.GetActor();
		if (HitActor && HitActor != this)
		{
			IDMDamagedActor* DamagedActor = Cast<IDMDamagedActor>(HitActor);
			if (DamagedActor)
			{
				DamagedActor->TakeDamage();
				if (AttackFlipbookActorClass && AttackFlipbookAsset)
				{
					FActorSpawnParameters Params;
					Params.Owner = this;
					APaperFlipbookActor* FBActor = World->SpawnActor<APaperFlipbookActor>(AttackFlipbookActorClass, Center, FRotator::ZeroRotator, Params);
					if (FBActor)
					{
						UPaperFlipbookComponent* FBComp = FBActor->GetRenderComponent();
						FBComp->SetFlipbook(AttackFlipbookAsset);
						FBComp->PlayFromStart();

						float Length = FBComp->GetFlipbookLength();
						FTimerHandle Handle;
						World->GetTimerManager().SetTimer(Handle, [FBActor]() { FBActor->Destroy(); }, Length, false);
					}
				}
			}
		}
	}
}
