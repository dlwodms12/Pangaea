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

	//속성(매크로 지정 전)
	/*
	int HelthPoints = 500;
	float Strength = 10;
	float Armer = 3;
	float AttackRange = 6.0f;
	float AttackInterval = 1.2f;
	*/
	
	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	int HelthPoints = 500;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float Strength = 10.0f;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float Armer = 3.0f;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float AttackRange = 6.0f;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float AttackInterval = 1.2f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//속성
	int _HelthPoints;
	float _AttackCountingDown;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//함수(매크로 적용 전)
	/*
	int GetHelthPoints();
	bool IsKilled();
	bool CanAttack();
	*/

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter", meta = (DisplayName = "Get HP"))
	int GetHelthPoints();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter")
	bool IsKilled();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter")
	bool CanAttack();

	void Attack();
	void Hit(int damage);

protected:
	void DieProcess();
};
