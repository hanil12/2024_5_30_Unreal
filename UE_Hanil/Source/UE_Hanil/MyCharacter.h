// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyStatComponent.h"

#include "MyCharacter.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_DELEGATE(DelegateTest1);
DECLARE_DELEGATE_OneParam(DelegateTestOneParam, int32);
DECLARE_DELEGATE_TwoParams(DelegateTestTwoParams, int32 hp, int32 mp);
DECLARE_MULTICAST_DELEGATE(Delegate_AttackEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_AttackHit);

UCLASS()
class UE_HANIL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAttackEnded(class UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	virtual void AttackHit();

	// Stat 관련
	int GetCurHp() { return _statCom->GetCurHp(); }
	void AddAttackDamage(AActor* actor,int amount);

	void AddItemToCharacter(class AMyItem* item);
	void DropItemFromCharacter();
	
	Delegate_AttackEnded _attackEndedDelegate;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = Event, meta = (AllowPrivateAccess = "true"))
	FDelegate_AttackHit _attackHitEvent;
	
protected:
	virtual void Init();

	UFUNCTION()
	virtual void Disable();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttcking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int _curAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;

	// AttackHitPoint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;


	// Animation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAnimInstance* _animInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyStatComponent* _statCom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpbarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inven, meta = (AllowPrivateAccess = "true"))
	class UMyInvenComponent* _invenCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	class AAIController* _aiController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMyProjectile> _projectileClass;
};
