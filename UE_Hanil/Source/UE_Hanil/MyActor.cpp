// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _sm;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	if (mesh.Succeeded())
	{
		_sm->SetStaticMesh(mesh.Object);
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("BeginPlay"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("Tick : %f"), DeltaTime);

	if (GetAttachParentActor() != nullptr)
	{
		FVector parentV = GetAttachParentActor()->GetActorLocation();
		FVector myV = GetActorLocation();
		FRotator rot = UKismetMathLibrary::FindLookAtRotation(myV, parentV);

		SetActorRotation(rot);
	}
	else
	{
		FRotator rot = FRotator(0.0f, 90.0f, 0.0f);
		AddActorLocalRotation(rot * _rotationSpeed * DeltaTime);
	}

	FVector moveV = FVector(0.0f,_moveSpeed,0.0f);
	// AddActorWorldOffset(moveV * DeltaTime);
	// 2. SetActorLocation() 이 함수로 위와 똑같이 동작하게 만들기
	//AddActorLocalOffset(moveV * DeltaTime); 이 함수의 문제점 찾기

	// 3. Quaternion (사원수)
	// 사원수 회전에 대해서 조사해보기
}

