// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyInvenComponent.generated.h"

class AMyItem;

DECLARE_MULTICAST_DELEGATE_TwoParams(ItemAdded, int itemId, int itemIndex)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_HANIL_API UMyInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyInvenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(AMyItem* item);
	UFUNCTION()
	void DropItem();

	ItemAdded _itemAddedEvent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TArray<class AMyItem*> _items;
};
