// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyAIController::AMyAIController()
{
}

// 컨트롤러가 폰에 빙의하는 것을 Possess
void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 3.0f, true);
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AMyAIController::RandMove()
{
	auto currentPawn = GetPawn();

	if(!currentPawn->IsValidLowLevel())
		return;

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(naviSystem == nullptr)
		return;

	FNavLocation randLocation;

	if (naviSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 30.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, FVector::ZeroVector);
	}
}
