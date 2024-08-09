// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffectManager.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
AMyEffectManager::AMyEffectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CreateParticle("meleeAttack", "/Script/Engine.ParticleSystem'/Game/ParagonNarbash/FX/Particles/Abilities/Primary/FX/P_Narbash_Melee_Impact.P_Narbash_Melee_Impact'");
}

void AMyEffectManager::CreateParticle(FString name,FString path)
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> explosion(*path);
	{
		if (explosion.Succeeded())
		{
			UParticleSystem* particle = explosion.Object;
			_table.Add(name, particle);
		}
	}
}

// Called when the game starts or when spawned
void AMyEffectManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffectManager::Play(FString name, FVector location, FRotator rotator)
{
	if(_table.Contains(name) == false)
		return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _table[name], location, rotator);
}


