// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DMPlayer2P.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbookActor.h"
#include "PaperFlipbookComponent.h"
#include "Player/DMSharedController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperZDAnimInstance.h"
#include "Game/DMGameModeBase.h"
#include "Player/DMFollowingCamera.h"
#include "Engine/OverlapResult.h"



ADMPlayer2P::ADMPlayer2P()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player2P"));
	MoveComp->GravityScale = 0.0f;
	MoveComp->bUseSeparateBrakingFriction = true;
	MoveComp->BrakingFrictionFactor = 4.0f;
	MoveComp->BrakingFriction = 8.0f;
	MoveComp->DefaultLandMovementMode = EMovementMode::MOVE_Flying;
	MoveComp->MaxFlySpeed = 600.0f;
	MoveComp->BrakingDecelerationFlying = 100.0f;
}

void ADMPlayer2P::BeginPlay()
{
	Super::BeginPlay();
	
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();
	if (GM)
	{
		ADMGameModeBase* DMGM = Cast<ADMGameModeBase>(GM);
		if (DMGM)
		{
			MyCam = DMGM->GetMainCamera();
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

void ADMPlayer2P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MyCam)
	{
		FVector CamLocation = MyCam->GetActorLocation();
		FVector CurLocation = GetActorLocation();
		float Width = 1900.0f;
		float Height = 960.0f;
		float MinX = CamLocation.X - Width * 0.5f;
		float MaxX = CamLocation.X + Width * 0.5f;
		float MinZ = CamLocation.Z - Height * 0.5f;
		float MaxZ = CamLocation.Z + Height * 0.5f;
		if (CurLocation.X < MinX)
			CurLocation.X = MinX;
		else if (CurLocation.X > MaxX)
			CurLocation.X = MaxX;
		if (CurLocation.Z < MinZ)
			CurLocation.Z = MinZ;
		else if (CurLocation.Z > MaxZ)
			CurLocation.Z = MaxZ;
		SetActorLocation(CurLocation);
	}
}

void ADMPlayer2P::OnInputMoveTriggered(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>(); // ex) (1,0) (-1, 0) (0, 1) (0, -1)

	FVector MoveDirection = FVector(MoveVector.X, 0.0f, MoveVector.Y);

	const float Width = 1900.0f;
	const float Height = 960.0f;

	FVector CurLocation = GetActorLocation();
	FVector ScreenCenter = MyCam->GetActorLocation();

	float MinX = ScreenCenter.X - Width * 0.5f;
	float MaxX = ScreenCenter.X + Width * 0.5f;
	float MinZ = ScreenCenter.Z - Height * 0.5f;
	float MaxZ = ScreenCenter.Z + Height * 0.5f;

	if ((CurLocation.X < MinX && MoveDirection.X < 0) || (CurLocation.X > MaxX && MoveDirection.X > 0))
	{
		MoveDirection.X = 0.0f;
	}
	if ((CurLocation.Z < MinZ && MoveDirection.Z < 0) || (CurLocation.Z > MaxZ && MoveDirection.Z > 0))
	{
		MoveDirection.Z = 0.0f;
	}

	if (MoveDirection.SizeSquared() > 0.0f)
	{
		AddMovementInput(MoveDirection.GetSafeNormal());
	}

	if (MoveDirection.X == 0.0f)
		return;

	float Yaw = (MoveDirection.X < 0.0f) ? 0.0f : 180.0f;

	SetActorRotation(FRotator(0.0f, Yaw, 0.0f));
}

void ADMPlayer2P::Attack()
{
	UWorld* World = GetWorld();
	if (!World) return;

	const FVector LocalOffset(-40.0f, 0.0f, 0.0f);
	const FVector Center = GetActorLocation() + GetActorRotation().RotateVector(LocalOffset);

	const FVector BoxExtent(50.0f, 30.0f, 20.0f);

	TArray<FOverlapResult> Results;
	bool bHit = GetWorld()->OverlapMultiByProfile(
		Results,
		Center,
		GetActorRotation().Quaternion(),
		TEXT("Player2P"),
		FCollisionShape::MakeBox(BoxExtent)
	);

	for (const FOverlapResult& Result : Results)
	{
		AActor* HitActor = Result.GetActor();
		if (HitActor && HitActor != this)
		{
			if (AttackFlipbookActorClass && AttackFlipbookAsset)
			{
				FActorSpawnParameters Params;
				Params.Owner = this;
				// 여기서는 공격 박스의 Center에 스폰
				APaperFlipbookActor* FBActor = World->SpawnActor<APaperFlipbookActor>(AttackFlipbookActorClass,Center,FRotator::ZeroRotator,Params);
				if (FBActor)
				{
					UPaperFlipbookComponent* FBComp = FBActor->GetRenderComponent();
					FBComp->SetFlipbook(AttackFlipbookAsset);
					FBComp->PlayFromStart();

					// 플레이 길이만큼 기다렸다가 자동 파괴
					float Length = FBComp->GetFlipbookLength();
					FTimerHandle Handle;
					World->GetTimerManager().SetTimer(Handle,[FBActor]() { FBActor->Destroy(); },Length,false);
				}
			}
			// Hit logic here
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());
			// Example: Apply damage or any other logic
			// UGameplayStatics::ApplyDamage(HitActor, DamageAmount, GetController(), this, UDamageType::StaticClass());
		}
	}

	
	DrawDebugBox(World, Center, BoxExtent,
		Owner->GetActorRotation().Quaternion(),
		FColor::Red, false, 1.f, 0, 2.f);

}
