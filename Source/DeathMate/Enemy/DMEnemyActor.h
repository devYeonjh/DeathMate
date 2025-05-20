	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMPaperActorBase.h"
#include "Interface/DMDamagedActor.h"
#include "DMEnemyActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEnemyDieDelegate);

UCLASS(Abstract)
class DEATHMATE_API ADMEnemyActor : public ADMPaperActorBase, public IDMDamagedActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move(float DeltaTime) PURE_VIRTUAL(ADMEnemyActor::Move, );
	
	void SetActorLocation2D(FVector Pos);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	float SpiritAmount = 10.f;

	FORCEINLINE void SetMoveSpeed(float NewSpeed) { MoveSpeed = NewSpeed; }

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void TakeDamage() override;

	FOnEnemyDieDelegate OnEnemyDieAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DamageSound;
private:
	FVector Direction = FVector::ZeroVector; // 이동 방향 기본값 0, 0, 0
	FVector StartLocation;
	bool bMovingForward = true;

    float LifeTimer = 0.f;

};
