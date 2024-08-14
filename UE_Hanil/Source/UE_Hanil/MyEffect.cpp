// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Actor => SpawnWorld
	// Component = > CreateDefaultSubObject
	// UObeject => NewObejct<T> =>  프로그래머가 직접 지워줘야함

	_particleCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = _particleCom;

	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	_niagaraCom->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();

	
	_particleCom->OnSystemFinished.AddDynamic(this, &AMyEffect::End);
	End(_particleCom);

	_niagaraCom->OnSystemFinished.AddDynamic(this, &AMyEffect::EndNiagara);
	EndNiagara(_niagaraCom);
}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffect::Play(FVector location, FRotator rotator)
{
	if(_particleCom->IsActive() || _niagaraCom->IsActive())
		return;

	SetActorLocationAndRotation(location, rotator);
	_particleCom->ActivateSystem();
	_niagaraCom->ActivateSystem();
}

bool AMyEffect::IsPlaying()
{
	if(_particleCom->IsActive())
		return true;

	if(_niagaraCom->IsActive())
		return true;

	return false;
}

void AMyEffect::End(UParticleSystemComponent* particle)
{
	if(particle)
		particle->DeactivateSystem();
}

void AMyEffect::EndNiagara(UNiagaraComponent* particle)
{
	if(particle)
		particle->Deactivate();
}

