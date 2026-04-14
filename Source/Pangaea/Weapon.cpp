// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerAvatar.h"
#include "DefenseTower.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_StaticMesh);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	//this는 무기 액터 본인을 의미함
	//두번째 매개변수는 핸들러 이벤트 함수 주소를 의미함
	//무기 자체가 충돌 이벤트를 받음
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Holder == nullptr)
	{
		//무기를 아무도 안들고 있으면 회전
		FQuat rotQuat = FQuat(FRotator(0.0f, 300.0f * DeltaTime, 0.0f));
		AddActorLocalRotation(rotQuat);
	}
}


void AWeapon::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("Weapon overlapped"));

	//캐릭터인지 확인
	auto character = Cast<ACharacter>(OtherActor);
	if (character == nullptr)
	{
		return;
	}

	//아무도 안들고 있는 무기라면
	if (Holder == nullptr)
	{
		//플레이어인지 확인하고
		auto playerAvatar = Cast<APlayerAvatar>(character);
		if (playerAvatar != nullptr)
		{
			//무기의 주인을 등록
			Holder = character;

			//캐릭터가 들고 있는 모든 액터를 가져와서
			TArray<AActor*> attachedActors;
			OtherActor->GetAttachedActors(attachedActors, true);
			for (int i = 0; i < attachedActors.Num(); ++i)
			{
				//DetachFromActor 함수는 무기를 현재 위치에 떨어뜨리는 기능을 수행함
				//기존 가지고 있는 무기를 떨어뜨림
				attachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				attachedActors[i]->SetActorRotation(FQuat::Identity);
				AWeapon* weapon = Cast<AWeapon>(attachedActors[i]);
				//떨어뜨린 무기는 주인을 해제하고 바닥 아이템이 됨
				weapon->Holder = nullptr;
			}

			//첫번째 매개변수는 플레이어 캐릭터의 스켈레탈 메시를 전달
			//두번째 매개변수는 엔진이 정의한 enum값으로, 함수가 무기를 메시의 스켈레톤 타깃 노드에 장착하도록 함
			//세번째 매개변수는 타깃 소켓의 이름
			//등록한 무기를 장착함
			AttachToComponent(Holder->GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
		}
	}
	else if (IsWithinAttackRange(0.0f, OtherActor))
	{
		//if within attack range
		//Deal damage to the target (PlayerAvatar or enemy)
	}
}

bool AWeapon::IsWithinAttackRange(float AttackRange, AActor* Target)
{
	return (AttackRange <= 0.0f || FVector::Distance(Target->GetActorLocation(), GetActorLocation()) <= AttackRange);
}

