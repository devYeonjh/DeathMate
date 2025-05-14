// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/DMTrigger2PBase.h"
#include "Components/BoxComponent.h"

ADMTrigger2PBase::ADMTrigger2PBase()
{
	BoxComp->SetCollisionProfileName(TEXT("Trigger2P"));
}

void ADMTrigger2PBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADMTrigger2PBase::OnPlayerOverlap);
}

void ADMTrigger2PBase::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TriggerEvent(OtherActor);
}
