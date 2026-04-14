// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//액터에 메시 컴포넌트를 추가하기 위해 헤더 파일 추가
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
//*.generated.h 구문은 항상 include 구문 맨 마지막에 와야함
#include "DefenseTower.generated.h"

//블루프린트로 생성하기 위해 블루프린트 지정자 추가
UCLASS(Blueprintable)
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseTower();

	
	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int HelthPoints = 500;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int ShellDefense = 3;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float AttackRange = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float ReloadInterval = 1.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//파이어볼을 처리하기 위한 변수
	UClass* _FireballClass;

	//protected 속성값 = 해당 클래스와 자식 클래스에서만 접근 가능
	//게임이 플레이되는 동안 게임 플레이 상태를 보여주기 위해 변경됨.
	int _HelthPoints; //타워 체력 변수
	float _ReloadCountingDown; //0이 되기 전까지 다음 사격 수행 불가

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	//충돌을 감지하는 용도
	UStaticMeshComponent* _MeshComponent;

	//액터를 게임 레벨에서 3D 메시로 표현
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* _SphereComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//FORCEINLINE : 주소에 기반해 함수를 호출하는 대신 컴파일러에 코드를 복사해 붙여넣는 언리얼 엔진 매크로.
	//인라인 함수는 간단한 한줄짜리 함수의 경우 함수를 호출하지 않고 바로 함수 자체를 스크립트에 복사해 실행하는 것.
	//FORCEINLINE의 경우 강제로 인라인함수로 처리하라고 명령하는 것임
	//const를 함수 뒤에 붙여 함수가 내부 포인터나 참조를 통해 매개변수나 클래스 멤버를 수정하지 못하도록 막음
	FORCEINLINE USphereComponent* GetSphereComponent() const { return _SphereComponent; }
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return _MeshComponent; }

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower", meta = (DisplayName = "GetHP"))
	int GetHelthPoints();

	UFUNCTION(BlueprintPure, Category = "Pangaea|Defense Tower")
	bool IsDestroyed();

	UFUNCTION(BlueprintPure, Category = "Pangaea|Defense Tower")
	bool CanFire();
	
	void Fire(); //발사
	void Hit(int damage); //피격

protected:
	void DestroyProcess();
	//타깃 캐릭터의 포인터를 저장할 변수. 여기선 플레이어 하나이므로 포인터 타입을 APlayerAvatar*로 지정
	//APlayerAvatar 앞에 class 키워드를 추가한 이유는 PlayerAvatar.h 파일을 DefenseTower.h 파일에는 포함하지 않고 cpp 파일에만 포함시키기 위함임.
	class APlayerAvatar* _Target = nullptr;

	//SphereComponent가 플레이어 캐릭터가 범위 안에 들어오고 나갈 때 이벤트를 처리할 수 있도록 이벤트 핸들러 함수를 추가
	//OverlappedComponent : 이벤트를 발생시키는 컴포넌트
	//OtherActor : 영역에 들어오거나 나가는 액터의 포인터
	//OtherComponent : 다른 액터의 컴포넌트
	//OtherBodyIndex : 다른 액터의 바디인덱스
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex);

	/*
	UFUNCTION(BlueprintCallable)
	void OnMeshBeginOverlap(AActor* OtherActor);
	*/
	
};
