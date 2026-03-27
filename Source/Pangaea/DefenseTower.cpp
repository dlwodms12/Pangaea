// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//클래스 생성자에 컴포넌트를 생성
	//클래스의 컴포넌트는 클래스의 생성자 안에서 인스턴스화 돼야 함 = 액터 부품(컴포넌트)는 생성자에서 미리 만들어놔야 한다.
	//CreateDefaultSubobject<Class>(오브젝트 이름)은 괄호로 묶인 클래스 유형의 오브젝트를 인스턴스화한다.
	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	//이 액터의 루트 컴포넌트로 설정한다.
	SetRootComponent(_BoxComponent);

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//컴포넌트의 SetupAttachment() 함수를 호출해 이 컴포넌트를 _BoxComponent의 자식으로 붙인다.
	_MeshComponent->SetupAttachment(_BoxComponent);
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