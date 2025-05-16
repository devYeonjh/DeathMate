// Fill out your copyright notice in the Description page of Project Settings.


#include "DMPaperActorBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"


// Sets default values
ADMPaperActorBase::ADMPaperActorBase()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
}



