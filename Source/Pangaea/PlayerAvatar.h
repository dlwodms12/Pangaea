// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerAvatar.generated.h"

//블루프린트 지정자 추가
UCLASS(Blueprintable)
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
	int _HealthPoints;
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
	int GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter")
	bool IsKilled();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter")
	bool CanAttack();

	void Attack();
	void Hit(int damage);
	
	//클래스 외부에서 카메라와 스프링암 포인터를 검색하기 위한 게터함수
	//추가했다면 헤더파일에 컴포넌트 추가해야함.
	//이후 생성자에서 컴포넌트를 인스턴스화해야함
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const
	{
		return _springArmComponent;
	}

	FORCEINLINE UCameraComponent* GetCameraComponent() const
	{
		return _cameraComponent;
	}

protected:
	void DieProcess();

private:
	//SpringArmComponent와 CameraComponent의 포인터를 저장하기 위한 변수 정의
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _cameraComponent;
};
