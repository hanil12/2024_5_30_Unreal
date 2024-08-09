// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEffectManager.generated.h"

UCLASS()
class UE_HANIL_API AMyEffectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEffectManager();

protected:
	void CreateParticle(FString name, FString path);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Play(FString name, FVector location, FRotator rotator = FRotator::ZeroRotator);

private:
	int32 _poolCount = 5;
	TMap<FString, UParticleSystem*> _table;
};
