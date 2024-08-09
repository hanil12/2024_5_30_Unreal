// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyStatComponent.h"

#include "MyGameInstance.generated.h"

/**
 * 
 */
 class AMyUIManager;
 class AMyEffectManager;

 #define UIManager Cast<UMyGameInstance>(GetGameInstance())->GetUIManager()
 #define EffectManager Cast<UMyGameInstance>(GetGameInstance())->GetEffectManager()

UCLASS()
class UE_HANIL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();

	virtual void Init() override;

	FMyStatData* GetStatDataByLevel(int level);

	AMyUIManager* GetUIManager() { return _uiManager; }
	AMyEffectManager* GetEffectManager() { return _effectManager; }

private:
	UPROPERTY()
	class UDataTable* _statTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMyUIManager* _uiManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMyEffectManager* _effectManager;
};
