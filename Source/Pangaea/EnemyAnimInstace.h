// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstace.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Locomotion,
	Attack,
	Hit,
	Die
};

/**
 * 
 */
UCLASS()
class PANGAEA_API UEnemyAnimInstace : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Params")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Params")
	EEnemyState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Params")
	void OnStateAnimationEnds();
};
