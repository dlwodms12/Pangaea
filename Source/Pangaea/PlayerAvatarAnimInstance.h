// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAvatarAnimInstance.generated.h"

/**
 * 
 */

//애니메이션 상태 값을 열거형으로 표현함
//EPlayerState 변수는 각 4개의 값 중 하나에만 할당된다.
//uint8 은 컴파일러에 값을 저장하기 위해 8비트를 예약한다는 것을 의미함.
//명시하지 않을 경우 일반적으로 32비트를 소모함
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Locomotion = 0, //각 애니메이션을 블렌딩하는 상태
	Attack, //공격 상태
	Hit, //피격 상태
	Die //사망
};

UCLASS()
class PANGAEA_API UPlayerAvatarAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	//Locomotion일 때 애니메이션을 보간하는데 사용하기 위한 Speed 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttacking;

//열거형 값을 할당받기 위한 State 변수
UPROPERTY(EditAnywhere, BlueprintReadWrite)
EPlayerState State;

//애니메이션이 종료됐을 때 State의 변경을 담당하는 함수
UFUNCTION(BlueprintCallable)
void OnStateAnimationEnds();

};
