// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenComponent.h"

#include "MyItem.h"

// Sets default values for this component's properties
UMyInvenComponent::UMyInvenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMyInvenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInvenComponent::AddItem(AMyItem* item)
{
	_items.Add(item);
	_itemAddedEvent.Broadcast(item->_itemId, _items.Num() - 1);
}

void UMyInvenComponent::DropItem()
{
	// Drop
	if (_items.Num() == 0)
		return;

	UE_LOG(LogTemp, Log, TEXT("Item Drop"));

	int itemSize = _items.Num();
	auto item = _items.Pop();
	_itemAddedEvent.Broadcast(-1, itemSize - 1);

	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector playerPos = GetOwner()->GetActorLocation();
	playerPos.Z = 0.0f;
	FVector itemPos = playerPos + FVector(X, Y, 0.0f);
	item->SetItemPos(itemPos);
}

