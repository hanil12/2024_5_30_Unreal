// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Deco_CanAttack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "MyPlayer.h"

UBT_Deco_CanAttack::UBT_Deco_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBT_Deco_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	if(currentPawn == nullptr || target == nullptr)
		return false;

	float distance = target->GetDistanceTo(currentPawn);

	return distance < 400.0f;

	return result;
}
