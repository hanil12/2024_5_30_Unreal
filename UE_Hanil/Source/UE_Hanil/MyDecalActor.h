// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MyDecalActor.generated.h"

/**
 * 
 */
 DECLARE_MULTICAST_DELEGATE_OneParam(FieldAttack, FVector);

UCLASS()
class UE_HANIL_API AMyDecalActor : public ADecalActor
{
	GENERATED_BODY()
public:
	AMyDecalActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Active(FVector location);
	void DeActiveEvent(FVector location);

	FieldAttack _fieldAttackDelegate;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _areaRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _delayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	float _runTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	bool _bIsPlay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DECAL, meta = (AllowPrivateAccess = "true"))
	bool _bLoop = false;
};
