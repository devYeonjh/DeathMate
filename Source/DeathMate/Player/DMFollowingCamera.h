// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMFollowingCamera.generated.h"

class UCameraComponent;
class APaperTileMapActor;

UCLASS()
class DEATHMATE_API ADMFollowingCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMFollowingCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float MinX, MaxX;
	float MinZ, MaxZ;
	float CameraHalfWidth;
	float CameraHalfHeight;
	
	APaperTileMapActor* TileMapActor = nullptr;
	UCameraComponent* CameraComponent;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow")
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow")
	FVector FollowOffset = FVector(0.f, 500.f, 200.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow")
	float SmoothSpeed = 5.f;

	FORCEINLINE float GetCameraHalfWidth() const { return CameraHalfWidth; }
	FORCEINLINE float GetCameraHalfHeight() const { return CameraHalfHeight; }

private:
	void RespawnAction(const FVector& Checkpoint);

	bool bTriedBeginPlayPawnSetup = false;


};
