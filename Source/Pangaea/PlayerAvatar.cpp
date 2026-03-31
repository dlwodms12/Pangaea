// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAvatarAnimInstance.h"

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

	//애니메이션 인스턴스와 이동속도 싱크 맞추기
	//애니메이션 인스턴스를 획득한다음 UPlayerAvatarAnimInstance 클래스 포인터가 되도록 캐스팅한 후 할당
	UPlayerAvatarAnimInstance* animInst = Cast<UPlayerAvatarAnimInstance>(GetMesh()->GetAnimInstance());
	//캐릭터의 무브먼트 컴포넌트에서 Velocity 벡터를 읽어온 다음, 벡터의 길이를 계산하고 Speed 변수에 할당함.
	animInst->Speed = GetCharacterMovement()->Velocity.Size2D();

	//카운팅다운과 공격 쿨다운 제한 시간이 동일하다면(충분히 시간이 지났다면)
	if (_AttackCountingDown == AttackInterval)
	{
		//공격 애니메이션으로 스테이트를 전환
		animInst->State = EPlayerState::Attack;
	}
	//아직 쿨다운 시간이 남았다면
	if (_AttackCountingDown > 0.0f)
	{
		//카운팅다운
		_AttackCountingDown -= DeltaTime;
	}
}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerAvatar::GetHealthPoints()
{
	return _HealthPoints;
}

bool APlayerAvatar::IsKilled()
{
	return (_HealthPoints <= 0.0f);
}

//공격을 수행할 수 있는지 판단
bool APlayerAvatar::CanAttack()
{
	//GetMesh()함수는 캐릭터의 SkeletalMesh 컴포넌트의 포인터를 반환
	//GetAnimInstance 함수는 SkeletalMesh와 연동돼 있는 애니메이션 인스턴스의 포인터를 반환
	//Attack 스테이트의 카운트다운 시간이 끝났다면 true를 반환하고 현재 스테이트를 Locomotion으로 변경
	//그렇지 않을 경우 false 반환
	UPlayerAvatarAnimInstance* animInst = Cast<UPlayerAvatarAnimInstance>(GetMesh()->GetAnimInstance());
	return (_AttackCountingDown <= 0.0f && animInst->State == EPlayerState::Locomotion);
}
//쿨다운 타이머 초기화
void APlayerAvatar::Attack()
{
	_AttackCountingDown = AttackInterval;
}
//액터 파괴
void APlayerAvatar::DieProcess()
{
	//Tick에서 캐릭터를 제외
	PrimaryActorTick.bCanEverTick = false;
	//캐릭터를 파괴 : 액터를 파괴하고 메모리를 대상으로 가비지 컬렉션을 수행한다음 메모리를 반환
	K2_DestroyActor();
	GEngine->ForceGarbageCollection(true);

	//위 세줄의 코드는 Destroy(); 한줄로 치환할 수 있음
}