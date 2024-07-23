// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//  대리자 : 함수 포인터, 함수 객체 => CallAble, 콜백함수
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("RightLeft"), this, &AMyPawn::RightLeft);
}

void AMyPawn::UpDown(float value)
{
	if (abs(value) >= 0.01)
		UE_LOG(LogTemp, Log, TEXT("UpDown : %f"), value);
}

void AMyPawn::RightLeft(float value)
{
	if(abs(value) >= 0.01)
		UE_LOG(LogTemp, Log, TEXT("RightLeft : %f"), value);
}

