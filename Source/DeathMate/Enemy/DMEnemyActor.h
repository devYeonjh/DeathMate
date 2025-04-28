	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMEnemyActor.generated.h"

//UENUM(BlueprintType)
//enum class EMovementType : uint8
//{
//	Ground UMETA(DisplayName = "Ground"), // 지형을 따라 움직이는 몬스터
//	Flying UMETA(DisplayName = "Flying") // 날아다니는 몬스터
//};


UCLASS(Abstract)
class DEATHMATE_API ADMEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move() PURE_VIRTUAL(ADMEnemyActor::Move, );
	float CurrentDeltaTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp; // 충돌 처리

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp; // 적의 외형

	UPROPERTY(EditAnywhere)
	int32 TraceRate = 80;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;
	void SetMoveSpeed(float NewSpeed);

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	FVector Direction = FVector::ZeroVector; // 이동 방향 기본값 0, 0, 0
	FVector StartLocation;
	bool bMovingForward = true;

};
