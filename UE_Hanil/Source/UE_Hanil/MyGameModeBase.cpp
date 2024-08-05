// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyAIController.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyCharacter>
	myCharacter(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/MyCharacter_BP.MyCharacter_BP_C'"));
	
	if (myCharacter.Succeeded())
	{
		DefaultPawnClass = myCharacter.Class;
	}

	static ConstructorHelpers::FClassFinder<AMyCharacter>
	myMonster(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/MyMonster_BP.MyMonster_BP_C'"));
	if (myMonster.Succeeded())
	{
		_monsterClass = myMonster.Class;
	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// APlayerController*
	FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(100,0.0f,0.0f);
	FRotator rotator = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
	
	// TODO : MyMonster.cpp
	//params.SpawnCollisionHandlingOverride
	//for (int i = 0; i < 3; i++)
	//{
	//	location.X += 500.0 * i;
	//	location.Z += 500.0f;

	//	AMyCharacter* SpawnedActor = GetWorld()->SpawnActor<AMyCharacter>(_monsterClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//	SpawnedActor->SetActorLocation(location);

	//	_monsters.Add(SpawnedActor);
	//}
}
