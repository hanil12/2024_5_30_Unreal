// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUIManager.h"

#include "Blueprint/UserWidget.h"
#include "MyInventoryUI.h"

// Sets default values
AMyUIManager::AMyUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UMyInventoryUI> invenClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/MyInventoryUI_BP.MyInventoryUI_BP_C'"));

	if (invenClass.Succeeded())
	{
		auto temp = invenClass.Class;
		//_invenWidget = CreateWidget<UMyInventoryUI>(GetWorld(), invenClass.Class);
	}
}

// Called when the game starts or when spawned
void AMyUIManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

