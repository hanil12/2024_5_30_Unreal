// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffectManager.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyEffect.h"

// Sets default values
AMyEffectManager::AMyEffectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CreateParticleClass(TEXT("Explosion"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/MyEffect_BP.MyEffect_BP_C'"));
}

void AMyEffectManager::CreateParticleClass(FString name,FString path)
{
	if (_classTable.Contains(name) == true)
	{
		UE_LOG(LogTemp, Error, TEXT("%s already exist in classTable"), *name);
		return;
	}

	static ConstructorHelpers::FClassFinder<AMyEffect> effect(*path);
	if (effect.Succeeded())
	{
		// classTable에 없었고, 잘 찾았을 때, classTable에 추가
		_classTable.Add(name);
		_classTable[name] = effect.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("cant find : %s"), *path);
		return;
	}
}

// Called when the game starts or when spawned
void AMyEffectManager::BeginPlay()
{
	Super::BeginPlay();
	CreateEffect();
}

void AMyEffectManager::CreateEffect()
{
	for (auto classPair : _classTable)
	{
		FString name = classPair.Key;

		_effectTable.Add(name);
		for (int i = 0; i < _poolCount; i++)
		{
			auto effect = GetWorld()->SpawnActor<AMyEffect>(classPair.Value,FVector::ZeroVector, FRotator::ZeroRotator);
			
			effect->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			_effectTable[name].Add(effect);
		}
	}
}

// Called every frame
void AMyEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffectManager::Play(FString name, FVector location, FRotator rotator)
{
}


