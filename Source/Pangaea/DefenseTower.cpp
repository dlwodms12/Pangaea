// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"
#include "PlayerAvatar.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Blueprint.h"
#include "Weapon.h"
#include "PangaeaCharacter.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//클래스 생성자에 컴포넌트를 생성
	//클래스의 컴포넌트는 클래스의 생성자 안에서 인스턴스화 돼야 함 = 액터 부품(컴포넌트)는 생성자에서 미리 만들어놔야 한다.
	//CreateDefaultSubobject<Class>(오브젝트 이름)은 괄호로 묶인 클래스 유형의 오브젝트를 인스턴스화한다.
	_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	//이 액터의 루트 컴포넌트로 설정한다.
	SetRootComponent(_SphereComponent);

	_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseTower::OnBeginOverlap);
	_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenseTower::OnEndOverlap);

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//컴포넌트의 SetupAttachment() 함수를 호출해 이 컴포넌트를 _SphereComponent의 자식으로 붙인다.
	_MeshComponent->SetupAttachment(_SphereComponent);

	//_FireballClass 변수가 BP_FireBall 정보를 저장하도록 처리
	static ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(TEXT("Blueprint'/Game/TopDown/Blueprints/BP_FireBall.BP_FireBall'"));
	if (blueprint_finder.Succeeded())
	{
		_FireballClass = (UClass*)blueprint_finder.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	//발사 시간을 결정
	//타워의 틱 타임을 1초에 두번으로 수정하여 1초에 두번만 발사
	SetActorTickInterval(0.5f);
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_Target != nullptr)
	{
		Fire();
	}

}

int ADefenseTower::GetHelthPoints()
{
	return _HelthPoints;
}

bool ADefenseTower::IsDestroyed()
{
	return (_HelthPoints <= 0.0f);
}

bool ADefenseTower::CanFire()
{
	return (_ReloadCountingDown <= 0.0f);
}

//발사 구현
void ADefenseTower::Fire()
{
	//생성자에서 BP_FireBall 클래스의 정보를 받아온 _FireballClass를 사용해 파이어볼을 생성함
	auto fireball = Cast<AProjectile>(GetWorld()->SpawnActor(_FireballClass));
	if (fireball == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("Fireball Fall"))
		return;
	}

	//디펜스 타워의 100 유닛 위치 앞에 파이어볼 생성
	FVector startLocation = GetActorLocation();
	startLocation.Z += 100.0f;
	//타깃의 위치 정보를 기반으로 현재 위치에서 FireBall을 발사
	FVector targetLocation = _Target->GetActorLocation();
	targetLocation.Z = startLocation.Z;
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(startLocation, targetLocation);
	fireball->SetActorLocation(startLocation);
	fireball->SetActorRotation(rotation);
}

void ADefenseTower::Hit(int damage)
{
}

void ADefenseTower::DestroyProcess()
{

}

//이벤트 핸들러 함수 구현 = 플레이어가 들어오면 타깃을 플레이어로 설정
void ADefenseTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap!"));
	APlayerAvatar* player = Cast<APlayerAvatar>(OtherActor);

	if (player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Targeting!"));
		_Target = player;
	}
}

//이벤트 핸들러 함수 구현 = 플레이어가 나가면 타깃을 초기화
void ADefenseTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (_Target != nullptr && OtherActor == _Target)
	{
		_Target = nullptr;
	}
}

//추후 수정 필요
void ADefenseTower::OnMeshBeginOverlap(AActor* OtherActor)
{
	AWeapon* weapon = Cast<AWeapon>(OtherActor);
	if (weapon == nullptr || weapon->Holder == nullptr)
	{
		return;
	}

	APangaeaCharacter* character = Cast<APangaeaCharacter>(weapon->Holder);
	if (character == nullptr) return;

	if (character->IsA(APlayerAvatar::StaticClass()) &&
		CanBeDamaged())
	{
		Hit(weapon->Strength);
	}
}
