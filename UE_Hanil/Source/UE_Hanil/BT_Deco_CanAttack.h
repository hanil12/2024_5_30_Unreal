// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BT_Deco_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class UE_HANIL_API UBT_Deco_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBT_Deco_CanAttack();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
