// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//액터에 메시 컴포넌트를 추가하기 위해 헤더 파일 추가
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
//*.generated.h 구문은 항상 include 구문 맨 마지막에 와야함
#include "DefenseTower.generated.h"

UCLASS()
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseTower();

	//public 속성 값 (=UPROPERTY 매크로 지정 전)
	//실시간으로 변경되지 않으며, 필요시 에디터에서 값을 수정하거나 시작할 때 수정함.
	/*
	int HelthPoints = 100; //타워 체력 초기값
	int ShellDefense = 2; //장갑 수치초기값
	float AttackRange = 15.0f; //공격 범위 초기값
	float ReloadInterval = 1.0f; //재장전 시간
	*/
	
	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int HelthPoints = 500;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int ShellDefense = 3;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float AttackRange = 6.0f;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float ReloadInterval = 1.0f;


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
	//UFUNCTION 매크로 적용 전
	/*
	int GetHelthPoints(); //타워 체력 값 반환
	bool IsDestroyed(); //파괴 여부
	bool CanFire(); //사격 가능 여부
	*/

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower", meta = (DisplayName = "GetHP"))
	int GetHelthPoints();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower", meta = (DisplayName = "GetHP"))
	bool IsDestroyed();

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower", meta = (DisplayName = "GetHP"))
	bool CanFire();
	
	void Fire(); //발사
	void Hit(int damage); //피격

protected:
	void DestroyProcess();

//액터에 추가되는 컴포넌트를 참조하기 위한 포인터 변수를 정의
private:
	//외부에서 확인 가능, 블루프린트로 읽기만 가능하며, 카테고리는 타워 컴포넌트이며, 프라이빗 변수를 에디터에서도 접근하는걸 허용한다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	//충돌을 감지하는 용도
	UBoxComponent* _BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	//액터를 게임 레벨에서 3D 메시로 표현
	UStaticMeshComponent* _MeshComponent;

//클래스 외부에서도 해당 컴포넌트에 접근할 수 있도록 게터함수 추가
public:
	//FORCEINLINE : 주소에 기반해 함수를 호출하는 대신 컴파일러에 코드를 복사해 붙여넣는 언리얼 엔진 매크로.
	//인라인 함수는 간단한 한줄짜리 함수의 경우 함수를 호출하지 않고 바로 함수 자체를 스크립트에 복사해 실행하는 것.
	//FORCEINLINE의 경우 강제로 인라인함수로 처리하라고 명령하는 것임
	//const를 함수 뒤에 붙여 함수가 내부 포인터나 참조를 통해 매개변수나 클래스 멤버를 수정하지 못하도록 막음
	FORCEINLINE UBoxComponent* GetBoxComponent() const
	{
		return _BoxComponent;
	}

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const
	{
		return _MeshComponent;
	}
};
