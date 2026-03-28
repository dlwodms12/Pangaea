// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"

// Sets default values
APlayerAvatar::APlayerAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//카메라와 스프링암 컴포넌트를 인스턴스화
	_springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//RootComponent에 springArmComponent 부착
	_springArmComponent->SetupAttachment(RootComponent);
	//씬 컴포넌트가 부모(Root)와 함께 회전할지, 아니면 독자적으로 회전할지 결정
	_springArmComponent->SetUsingAbsoluteRotation(true);
	//스프링암 길이 설정
	_springArmComponent->TargetArmLength = 800.f;
	//씬 컴포넌트가 부모를 기준으로 상대적인 회전을 할지 결정
	_springArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	//스프링암 컴포넌트에 충돌테스트가 적용될지 여부를 결정
	_springArmComponent->bDoCollisionTest = false;

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_cameraComponent->SetupAttachment(_springArmComponent, USpringArmComponent::SocketName);
	//cameraComponent의 회전이 폰의 회전에 따라 달라지는 시각/회전 제어에 영향을 받는지 결정
	_cameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerAvatar::GetHelthPoints()
{
	return _HelthPoints;
}

bool APlayerAvatar::IsKilled()
{
	return (_HelthPoints <= 0.0f);
}

bool APlayerAvatar::CanAttack()
{
	return (_AttackCountingDown <= 0.0f);
}
