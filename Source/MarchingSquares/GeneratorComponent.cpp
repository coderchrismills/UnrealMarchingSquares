// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneratorComponent.h"
#include "Components/ActorComponent.h"
#include "Components/TextRenderComponent.h"
#include "NodeActor.h"
#include "NodeConnectionActor.h"

// Sets default values for this component's properties
UGeneratorComponent::UGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters spawnParams;
	
	int32 numberOfRows = 10;
	int32 numberOfColumns = 10;
	int32 amount = numberOfRows*numberOfColumns;
	
	// from http://jacobzelko.com/marching-squares/
	// Jacob Zelko. Implementing Marching Squares. December 1st, 2020. http://jacobzelko.com
	bool values[10][10] = {
		{ false,  true,   true,   false,  false,  false,  true,   false,  true,   false },
		{ false,  true,   true,   false,  true,   false,  false,  true,   false,  false },
		{ false,  false,  true,   true,   false,  true,   true,   true,   false,  false },
		{ false,  false,  false,  true,   true,   false,  true,   true,   true,   false },
		{ false,  false,  true,   false,  false,  true,   false,  true,   false,  false },
		{ false,  false,  true,   true,   true,   true,   false,  true,   true,   false },
		{ false,  false,  false,  true,   false,  false,  true,   false,  false,  false },
		{ true,   true,   true,   false,  false,  true,   false,  false,  false,  false },
		{ false,  false,  true,   false,  false,  true,   true,   true,   false,  true  },
		{ false,  true,   true,   false,  true,   true,   false,  false,  false,  true  }
	};

	float spacing = 120.0f;
	AActor* parentActor = GetOwner();
	USceneComponent* rootComponent = nullptr;
	if (parentActor != nullptr)
	{
		rootComponent = parentActor->GetRootComponent();
	}
	 
	for (int32 c = 0; c < numberOfColumns; c++)
	{
		for (int32 r = 0; r < numberOfRows; r++)
		{
			FString name = FString::Printf(TEXT("Sphere-%i-%i"), r, c);
			FVector location = FVector(r * spacing, c * spacing, 0);
			ANodeActor* spawned = GetWorld()->SpawnActor<ANodeActor>(location, FRotator::ZeroRotator, spawnParams);
			spawned->SetActorLabel(name);
			spawned->Initialize(values[r][c]);
			spawned->AttachToActor(parentActor, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

	for (int32 c = 0; c < numberOfColumns - 1; c++)
	{
		for (int32 r = 0; r < numberOfRows - 1; r++)
		{
			int32 bottomLeft = values[r][c + 1] ? 1 : 0;
			int32 bottomRight = values[r + 1][c + 1] ? 1 : 0;
			int32 topRight = values[r + 1][c] ? 1 : 0;
			int32 topLeft = values[r][c] ? 1 : 0;

			int32 isoValue = topLeft * 8 + topRight * 4 + bottomRight * 2 + bottomLeft * 1;

			FString name = FString::Printf(TEXT("Connection-%i-%i-%i"), r, c, isoValue);
			FVector location = FVector((r * spacing) + (spacing / 2), (c * spacing) + (spacing / 2), 0);
			ANodeConnectionActor* spawned = GetWorld()->SpawnActor<ANodeConnectionActor>(location, FRotator::ZeroRotator, spawnParams);
			spawned->SetActorLabel(name);
			spawned->Initialize(isoValue);
			spawned->AttachToActor(parentActor, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}


// Called every frame
void UGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
