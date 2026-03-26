// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerAvatar.generated.h"

UCLASS()
class PANGAEA_API APlayerAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();

	//加己
	int HelthPoints = 500;
	float Strength = 10;
	float Armer = 3;
	float AttackRange = 6.0f;
	float AttackInterval = 1.2f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//加己
	int _HelthPoints;
	float _AttackCountingDown;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//窃荐
	int GetHelthPoints();
	bool IsKilled();
	bool CanAttack();
	void Attack();
	void Hit(int damage);

protected:
	void DieProcess();
};
