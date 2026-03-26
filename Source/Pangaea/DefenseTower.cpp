// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ADefenseTower::GetHelthPoints()
{
	return _HelthPoints;
}

bool ADefenseTower::IsDestroyed()
{
	return (_HelthPoints > 0.0f);
}

bool ADefenseTower::CanFire()
{
	return (_ReloadCountingDown <= 0.0f);
}