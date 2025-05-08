// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/DMTrigger1PBase.h"
#include "Components/BoxComponent.h"

ADMTrigger1PBase::ADMTrigger1PBase()
{
	BoxComp->SetCollisionProfileName(TEXT("Trigger1P"));
}

void ADMTrigger1PBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADMTrigger1PBase::OnPlayerOverlap);
}

void ADMTrigger1PBase::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Overlapped Trigger"));

	TriggerEvent(OtherActor);
}

