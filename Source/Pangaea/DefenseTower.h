// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseTower.generated.h"

UCLASS()
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseTower();

	//public 속성 값
	//실시간으로 변경되지 않으며, 필요시 에디터에서 값을 수정하거나 시작할 때 수정함.
	int HelthPoints = 100; //타워 체력 초기값
	int ShellDefense = 2; //장갑 수치초기값
	float AttackRange = 15.0f; //공격 범위 초기값
	float ReloadInterval = 1.0f; //재장전 시간


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//protected 속성값 = 해당 클래스와 자식 클래스에서만 접근 가능
	//게임이 플레이되는 동안 게임 플레이 상태를 보여주기 위해 변경됨.
	int _HelthPoints; //타워 체력 변수
	float _ReloadCountingDown; //0이 되기 전까지 다음 사격 수행 불가

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//public 함수
	//모든 곳에서 호출 가능한 함수
	int GetHelthPoints(); //타워 체력 값 반환
	bool IsDestroyed(); //파괴 여부
	bool CanFire(); //사격 가능 여부
	void Fire(); //발사
	void Hit(int damage); //피격

protected:
	void DestroyProcess();
};
