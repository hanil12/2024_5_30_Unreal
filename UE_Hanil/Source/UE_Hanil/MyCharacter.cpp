// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO 
	// skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonNarbash/Characters/Heroes/Narbash/Meshes/Narbash.Narbash'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// 상속관계 설정
	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f,0.0f,0.0f));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	auto animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	// 몽타주가 끝날 때 _isAttack 을 false로 만들어줬으면 좋겠다.
	animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackEnded);
	animInstance->_attackDelegate.AddUObject(this, &AMyCharacter::AttackHit);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		// Jumping
		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &AMyCharacter::JumpA);
		
		// Attack
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyCharacter::AttackA);
	}
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// TODO : 
	// 1. hp -=  Damage
	// 2. 공격자 이름 출력

	return 0.0f;
}

void AMyCharacter::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Error, TEXT("Attack End!!!"));
	_isAttcking = false;
}

void AMyCharacter::AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false,this);

	float attackRange = 500.0f;
	float attackRadius = 100.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
	hitResult,
	GetActorLocation(),
	GetActorLocation() + GetActorForwardVector() * attackRange,
	FQuat::Identity,
	ECollisionChannel::ECC_GameTraceChannel2,
	FCollisionShape::MakeSphere(attackRadius),
	params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	UE_LOG(LogTemp, Log, TEXT("%s"), *vec.ToString());
	FVector center = GetActorLocation() + vec * 0.5f;
	
	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		//UE_LOG(LogTemp, Log, TEXT("HitActor : %s"), *hitResult.GetActor()->GetName());
		drawColor = FColor::Red;

		// TODO : TakeDamage
	}
	DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor,false, 2.0f);
}

void AMyCharacter::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		_vertical = MovementVector.Y;
		_horizontal = MovementVector.X;

		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
}

void AMyCharacter::JumpA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		ACharacter::Jump();
	}
}

void AMyCharacter::AttackA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttcking == false)
	{
		auto myAnimI = GetMesh()->GetAnimInstance();
		Cast<UMyAnimInstance>(myAnimI)->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		Cast<UMyAnimInstance>(myAnimI)->JumpToSection(_curAttackIndex);
	}
}

