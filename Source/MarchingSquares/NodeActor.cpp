// Fill out your copyright notice in the Description page of Project Settings.
#include "NodeActor.h"

// Sets default values
ANodeActor::ANodeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		dynamicMesh = SphereVisualAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> PineAsset(TEXT("/Game/StarterContent/Materials/M_Wood_Pine"));
	if (PineAsset.Succeeded())
	{
		pineMaterial = PineAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> WalnutAsset(TEXT("/Game/StarterContent/Materials/M_Wood_Walnut"));
	if (WalnutAsset.Succeeded())
	{
		walnutMaterial = WalnutAsset.Object;
	}
}

// Called when the game starts or when spawned
void ANodeActor::BeginPlay()
{
	Super::BeginPlay();
	dynamicMeshComponent = NewObject<UStaticMeshComponent>(this);
	dynamicMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	dynamicMeshComponent->RegisterComponent();
	dynamicMeshComponent->SetStaticMesh(dynamicMesh);
	dynamicMeshComponent->SetWorldScale3D(FVector(0.5, 0.5, 0.5));
}

void ANodeActor::Initialize(bool enabled)
{
	isEnabled = enabled;
	if (isEnabled)
	{
		dynamicMeshComponent->SetMaterial(0, walnutMaterial);
	}
	else
	{
		dynamicMeshComponent->SetMaterial(0, pineMaterial);
	}
}

// Called every frame
void ANodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

