// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Dungeon/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	FVector StartLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector EndLocation = StartLocation + (ForwardVector * 100.f);

	DRAW_SPHERE(StartLocation);
	DRAW_VECTOR(StartLocation, EndLocation);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

