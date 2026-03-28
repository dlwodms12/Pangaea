// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	//초기화 작업 수행
	//Tick 함수를 활성화해 게임 프레임을 업데이트할 때마다 캐릭터의 Tick 함수 호출
	PrimaryActorTick.bCanEverTick = true;
	//탑다운 게임에선 캐릭터가 달리는 방향만 정해지면 되므로 플레이어가 캐릭터를 회전하지 않도록 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//characterMovement를 통해 캐릭터가 달리는 방향이 제어됨.
	auto* characterMovement = GetCharacterMovement();
	//캐릭터가 이동하는 방향으로 자동으로 몸을 돌림
	characterMovement->bOrientRotationToMovement = true;
	//회전 속도 설정 (초당 640도)
	characterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	//캐릭터가 Z축 이동하지 않도록 특정 평면에 가둠
	characterMovement->bConstrainToPlane = true;
	//캐릭터가 시작할 때 평면에 딱 붙도록 설정
	characterMovement->bSnapToPlaneAtStart = true;
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
