// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_Task_FindRandomPos.generated.h"

/**
 * 
 */
UCLASS()
class UE_HANIL_API UBT_Task_FindRandomPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBT_Task_FindRandomPos();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
