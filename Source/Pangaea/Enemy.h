// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PANGAEA_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	int HealthPoints = 100;

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float Strenth = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float Armor = 1;

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float AttackRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float AttackInterval = 3.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int _HelthPoints;
	float _AttackCountingDown;
	//현재 타깃의 포인터를 받음
	APawn* _chasedTarget = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy", meta = (DisplayName = "Get HP"))
	int GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	bool IsKilled();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	bool CanAttack();

	//PawnSensingComponent가 OnSeePawn 이벤트를 트리거하면 블르프린트가 chase함수를 호출해 타깃을 설정하고 쫒아감.
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	void Chase(APawn* targetPawn);

	void Attack();
	void Hit(int damage);
	void DieProcess();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAceess = "true"))
	//감지하는 영역 안으로 플레이어 캐릭터가 들어왔는지 체크하는 컴포넌트
	//영역 안에서 PC가 감지되면 _chasedTarget 변수에 PC가 설정됨
	//벗어나면 다시 nullptr
	class UPawnSensingComponent* PawnSensingComponent;
};
