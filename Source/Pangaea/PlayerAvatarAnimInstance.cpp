// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatarAnimInstance.h"
#include "PlayerAvatar.h"

void UPlayerAvatarAnimInstance::OnStateAnimationEnds()
{
	//공격 애니메이션이 끝나면 다시 기본 상태로 복귀
	if (State == EPlayerState::Attack)
	{
		State = EPlayerState::Locomotion;
	}
	else
	{
		//이 AnimInstance를 사용하는 캐릭터를 가져와서 APlayerAvatar로 캐스팅
		auto ownerActor = this->GetOwningActor();
		auto playerAvatar = Cast<APlayerAvatar>(ownerActor);

		if (playerAvatar == nullptr)
		{
			UE_LOG(LogAnimation, Error, TEXT("The owner actor is not a PlayerAvatar!"));
			return;
		}
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
			//...
		}
	}
}
