// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDecalActor.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"

void AMyDecalActor::BeginPlay()
{
	Super::BeginPlay();

	// TODO : 
	// size  최소
	GetDecal()->DecalSize.Z = _minSize.X;
	GetDecal()->DecalSize.Y = _minSize.Y;
}

void AMyDecalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// TODO : 
	// 점점 늘리다가 최대사이즈에 도달하면
	// - 이벤트
	if (GetDecal()->DecalSize.Z >= _maxSize.X)
	{
		_fieldAttackDelegate.Execute(GetActorLocation());
		GetDecal()->DecalSize.Z = _minSize.X;
		GetDecal()->DecalSize.Y = _minSize.Y;

		return;
	}

	// size 점점 늘리기
	GetDecal()->DecalSize.Z += DeltaTime;
	GetDecal()->DecalSize.Y += DeltaTime;
}
