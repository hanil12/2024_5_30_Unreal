// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEffectManager.generated.h"

class AMyEffect;

UCLASS()
class UE_HANIL_API AMyEffectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEffectManager();

protected:
	void CreateParticleClass(FString name, FString path);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateEffect();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Play(FString name, FVector location, FRotator rotator = FRotator::ZeroRotator);

private:
	int32 _poolCount = 5;

	UPROPERTY()
	TMap<FString, TSubclassOf<AMyEffect>> _classTable;

	TMap<FString, TArray<AMyEffect*>> _effectTable;

	UPROPERTY()
	class USceneComponent* _rootComponent;
};
