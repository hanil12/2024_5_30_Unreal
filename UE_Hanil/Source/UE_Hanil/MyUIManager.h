// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyUIManager.generated.h"

class UUserWidget;
class UMyInventoryUI;

UENUM()
enum class UIType : int32
{
	CrossHair,
	Inventory,
};

UCLASS()
class UE_HANIL_API AMyUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenWidget(UIType type);
	void CloseWidget(UIType type);
	void CloseAll();

	UMyInventoryUI* GetInvenUI() { return _invenWidget; }
	UUserWidget* GetCrossHair() { return _crossHair; }

private:
	UPROPERTY()
	TArray<UUserWidget*> _widgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	UMyInventoryUI* _invenWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	UUserWidget* _crossHair;
};
