	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMEnemyActor.generated.h"

UCLASS()
class DEATHMATE_API ADMEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	float MoveSpeed = 1500.0f;

	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:


private:
	FVector Direction = FVector::ZeroVector; // 이동 방향 기본값 0, 0, 0

};
