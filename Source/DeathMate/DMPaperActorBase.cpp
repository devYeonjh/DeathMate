// Fill out your copyright notice in the Description page of Project Settings.


#include "DMPaperActorBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ADMPaperActorBase::ADMPaperActorBase()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
}



