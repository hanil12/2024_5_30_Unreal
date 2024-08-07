// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonster.h"

#include "MyAIController.h"
#include "MyAnimInstance.h"

AMyMonster::AMyMonster()
{
}

void AMyMonster::BeginPlay()
{
	Super::BeginPlay();

	_aiController = Cast<AMyAIController>(GetController());
}

void AMyMonster::Attack_AI()
{
	if(_statCom->IsDead())
		return;

	if (_isAttcking == false && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);
	}
}