// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "PlayerAvatar.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_MeshComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//헤더 파일에서 설정한 Lifespan의 값만큼만 유지할 수 있음
	_LifeCountingDown = Lifespan;
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_LifeCountingDown > 0.0f)
	{
		//공의 현재 회전을 사용해 단위 전진 벡터를 회전시킨 다음 회전된 벡터를 속도와 델타 시간에 곱함
		//새로운 위치는 현재 위치와 속도를 더한 값임
		FVector currentLocation = GetActorLocation();
		FVector vel = GetActorRotation().RotateVector(FVector::ForwardVector) * Speed * DeltaTime;
		FVector nextLocation = currentLocation + vel;
		SetActorLocation(nextLocation);

		//Ray cast check
		//LineTrace 함수를 호출하기 위한 변수로 사용됨
		FHitResult hitResult;
		//LineTrace 함수에 어떤 유형의 오브젝트가 충돌해야 하는지 알려주는 네번째 매개변수로 사용
		FCollisionObjectQueryParams objCollisionQueryParams;
		//LineTrace 함수의 트레이싱 라인이 폰 타깃에 부딪혔는지 여부만을 체크한다는 의미
		objCollisionQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		//두번째와 세번째 매개변수는 트레이싱 라인의 시작지점과 종료지점임
		//폰에 부딪히면 true값을 반환, 스크립트는 피격된 폰이 Player인지 확인하고 그 결과가 true라면 대미지를 가함
		if (GetWorld()->LineTraceSingleByObjectType(hitResult, currentLocation, nextLocation, objCollisionQueryParams))
		{
			auto playerAvatar = Cast<APlayerAvatar>(hitResult.GetActor());
			if (playerAvatar != nullptr)
			{
				playerAvatar->Hit(Damage);

				PrimaryActorTick.bCanEverTick = false;
				Destroy();
			}
		}

		//Reduce time
		_LifeCountingDown -= DeltaTime;
	}
	else
	{
		PrimaryActorTick.bCanEverTick = false;
		Destroy();
	}

}

