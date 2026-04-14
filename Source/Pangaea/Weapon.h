// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Weapon.generated.h"

UCLASS()
class PANGAEA_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	//무기가 플레이어에 장착됐을 때나 적이 무기를 집어들었을 때 설정됨. 
	//또한 무기를 획득하지 않은 상태에서 무기가 회전하고 있는지 여부를 판단할 때도 사용.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACharacter* Holder = nullptr;

	//타깃에 전달되는 대미지를 계산할 때 사용
	UPROPERTY(EditAnywhere, Category = "Weapon Params")
	float Strength = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* _StaticMesh;

	UFUNCTION()
	//BeginOverlap 핸들러 함수
	//기능이 동작하려면 Weapon.cpp 에서 BeginPlay() 함수 무기 액터의 델리게이트 이벤트와 이 함수를 바인딩해야함
	void OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//추후 구현
	bool IsWithinAttackRange(float AttackRange, AActor* Target);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};