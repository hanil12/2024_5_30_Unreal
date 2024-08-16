// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	_collider->InitCapsuleSize(70,20);

	_meshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	_movementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));

	RootComponent = _meshCom;
	_collider->SetupAttachment(_meshCom);
}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator curRotation = GetActorRotation();

	curRotation.Yaw += DeltaTime * 200.0f;
	curRotation.Pitch += DeltaTime * 200.0f;

	SetActorRotation(curRotation);
}

void AMyProjectile::FireInDirection(const FVector& ShootDirection)
{
	_movementCom->Velocity = ShootDirection * _movementCom->InitialSpeed;
}
