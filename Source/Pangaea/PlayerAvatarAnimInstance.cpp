// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatarAnimInstance.h"
#include "PlayerAvatar.h"

void UPlayerAvatarAnimInstance::OnStateAnimationEnds()
{
	//현재 Attack State라면, 애니메이션이 종료될 때 이 함수를 호출한다.
	//이 함수 호출을 통해 Locomotion State로 돌아간다.
	if (State == EPlayerState::Attack)
	{
		State = EPlayerState::Locomotion;
	}
	else
	{
		auto playerAvatar = Cast<APlayerAvatar>(this->GetOwningActor());
		//피격 당했다면
		if (State == EPlayerState::Hit)
		{
			//체력이 남아있으면 다시 이동 상태
			if (playerAvatar->GetHealthPoints() > 0.0f)
			{
				State = EPlayerState::Locomotion;
			}
			//체력이 0이하면 사망 상태로 전환
			else
			{
				State = EPlayerState::Die;
			}
		}
		//사망 애니메이션이 끝난 뒤 처리
		else if (State == EPlayerState::Die)
		{
			playerAvatar->DieProcess();
		}
	}
}
