// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Enemy.h"

//적과 적이 추적하고 있는 타깃의 거리를 계산해 그 거리가 적이 공격할 수 있는 범위보다 짧은지를 판단
//타깃이 공격범위 안에 들어와있고 적이 공격을 수행할 수 있는 상태라면 Attack 함수를 호출
void AEnemyController::MakeAttckDecision(APawn* targetPawn)
{
	auto controlledCharacter = Cast<AEnemy>(GetPawn());
	auto dist = FVector::Dist2D(targetPawn->GetActorLocation(), GetPawn()->GetTargetLocation());
	if (dist <= controlledCharacter->AttackRange && controlledCharacter->CanAttack())
	{
		controlledCharacter->Attack();
	}
}

