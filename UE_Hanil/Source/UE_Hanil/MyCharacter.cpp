// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// UI
#include "MyGameInstance.h"
#include "MyUIManager.h"
#include "MyInventoryUI.h"

#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "Engine/DamageEvents.h"
#include "Math/UnrealMathUtility.h"
#include "MyItem.h"
#include "MyStatComponent.h"
#include "MyInvenComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MyHpBar.h"
#include "MyPlayerController.h"
#include "Components/Button.h"

// AI
#include "MyAIController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-88.0f), FRotator(0.0f, -90.0f, 0.0f));



	RootComponent = GetCapsuleComponent();

	// Stat
	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));
	_statCom->_deathDelegate.AddLambda([this]()-> void { this->GetController()->UnPossess(); });

	_hpbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_hpbarWidget->SetupAttachment(GetMesh());
	_hpbarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpbarWidget->SetRelativeLocation(FVector(0.0f,0.0f, 230.0f));

	_invenCom = CreateDefaultSubobject<UMyInvenComponent>(TEXT("Inventory_Com"));

	static ConstructorHelpers::FClassFinder<UUserWidget> hpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/MyHpBar_BP.MyHpBar_BP_C'"));

	if (hpBar.Succeeded())
	{
		_hpbarWidget->SetWidgetClass(hpBar.Class);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (_animInstance->IsValidLowLevel())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCharacter::AttackHit);
		_animInstance->_deathDelegate.AddUObject(this, &AMyCharacter::Disable);
	}

	_statCom->SetLevelAndInit(1);

	_hpbarWidget->InitWidget();
	auto hpBar = Cast<UMyHpBar>(_hpbarWidget->GetUserWidgetObject());

	if (hpBar)
	{
		_statCom->_hpChangedDelegate.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);
	}
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = -_statCom->AddCurHp(-Damage);

	return damaged;
}

void AMyCharacter::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttcking = false;
	_attackEndedDelegate.Broadcast();
}

void AMyCharacter::AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false,this);

	float attackRange = 500.0f;
	float attackRadius = 100.0f;
	FQuat quat = FQuat::Identity;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
	hitResult,
	GetActorLocation(),
	GetActorLocation() + GetActorForwardVector() * attackRange,
	quat,
	ECollisionChannel::ECC_GameTraceChannel2,
	FCollisionShape::MakeCapsule(attackRadius, attackRange),
	params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;
	
	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		FDamageEvent damageEvent;
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), damageEvent, GetController(), this);

	}
	//DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor,false, 2.0f);
	DrawDebugCapsule(GetWorld(), center, attackRange, attackRadius, quat, drawColor,false,2.0f);
}

void AMyCharacter::AddAttackDamage(AActor* actor, int amount)
{
	// actor는 나의 공격력을 버프해준 대상

	_statCom->AddAttackDamage(amount);
}

void AMyCharacter::AddItemToCharacter(AMyItem* item)
{
	_invenCom->AddItem(item);
}

void AMyCharacter::DropItemFromCharacter()
{
	_invenCom->DropItem();
}

void AMyCharacter::Init()
{
	_statCom->Reset();
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;
	
	if (_aiController && GetController() == nullptr)
	{
		auto aI_Controller = Cast<AMyAIController>(_aiController);
		if(aI_Controller)
			aI_Controller->Possess(this);
	}
}

void AMyCharacter::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
	auto controller = GetController();
	if(controller)
		GetController()->UnPossess();
	UnPossessed();
}

