// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(DeathDelegate);

USTRUCT()
struct FMyStatData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 attack;
};

DECLARE_MULTICAST_DELEGATE_OneParam(HpChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_HANIL_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Reset();

	int32 GetCurHp() { return _curHp; }
	int32 GetAttackDamage() { return _attackDamage; }
	float HpRatio() { return _curHp / (float)_maxHp; }

	void SetLevelAndInit(int level);

	void SetHp(int32 hp);
	int AddCurHp(float amount);
	void AddAttackDamage(float amount);

	bool IsDead() { return _curHp <=0 ;}

	HpChanged _hpChangedDelegate;
	DeathDelegate _deathDelegate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	int32 _curHp = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	int32 _maxHp = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	int32 _attackDamage = 1;
};
