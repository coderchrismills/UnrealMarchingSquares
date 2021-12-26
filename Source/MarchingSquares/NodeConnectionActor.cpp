// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeConnectionActor.h"

// Sets default values
ANodeConnectionActor::ANodeConnectionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> PipeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe"));
	if (PipeVisualAsset.Succeeded())
	{
		dynamicMesh = PipeVisualAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MetalMaterialAsset(TEXT("/Game/StarterContent/Materials/M_Wood_Oak"));
	if (MetalMaterialAsset.Succeeded())
	{
		pipeMaterial = MetalMaterialAsset.Object;
	}
}

// Called when the game starts or when spawned
void ANodeConnectionActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANodeConnectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANodeConnectionActor::Initialize(int32 iv)
{
	isoValue = iv;

	if (isoValue == 0 || isoValue == 15)
	{
		return;
	}

	FVector actorLocation = this->GetActorLocation();
	float length = 60; // magic! (actually 1/2 the spacing in the generator
	float dx = (length/2);
	float dy = (length/2);
	FVector quadrant1 = FVector(actorLocation.X - dx, actorLocation.Y - dy, 0);
	FVector quadrant2 = FVector(actorLocation.X + dx, actorLocation.Y - dy, 0);
	FVector quadrant3 = FVector(actorLocation.X + dx, actorLocation.Y + dy, 0);
	FVector quadrant4 = FVector(actorLocation.X - dx, actorLocation.Y + dy, 0);

	if (isoValue == 1 || isoValue == 14)
	{
		FRotator rotation = FRotator(0, -45, 0);
		FVector location = quadrant4;
		CreateMesh(rotation, location);
	}
	else if (isoValue == 2 || isoValue == 13)
	{
		FRotator rotation = FRotator(0, 45, 0);
		FVector location = quadrant3;
		CreateMesh(rotation, location);
	}
	else if (isoValue == 3 || isoValue == 12)
	{
		FRotator rotation = FRotator(0, 90, 0);
		FVector location = actorLocation;
		CreateMesh(rotation, location);
	}
	else if (isoValue == 4 || isoValue == 11)
	{
		FRotator rotation = FRotator(0, -45, 0);
		FVector location = quadrant2;
		CreateMesh(rotation, location);
	}
	else if (isoValue == 5)
	{
		FRotator rotation = FRotator(0, 45, 0);
		FVector location1 = quadrant1;
		CreateMesh(rotation, location1);
		FVector location2 = quadrant3;
		CreateMesh(rotation, location2);
	}
	else if (isoValue == 6 || isoValue == 9)
	{
		FRotator rotation = FRotator::ZeroRotator;
		FVector location = actorLocation;
		CreateMesh(rotation, location);
	}
	else if (isoValue == 7 || isoValue == 8)
	{
		FRotator rotation = FRotator(0, 45, 0);
		FVector location = quadrant1;
		CreateMesh(rotation, location);
	}
	else if (isoValue == 10)
	{
		FRotator rotation = FRotator(0, -45, 0);
		FVector location1 = quadrant2;
		CreateMesh(rotation, location1);
		FVector location2 = quadrant4;
		CreateMesh(rotation, location2);
	}
}

void ANodeConnectionActor::CreateMesh(FRotator rotation, FVector localOffset)
{
	auto dynamicMeshComponent = NewObject<UStaticMeshComponent>(this);
	dynamicMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	dynamicMeshComponent->RegisterComponent();
	dynamicMeshComponent->SetStaticMesh(dynamicMesh);
	dynamicMeshComponent->SetMaterial(0, pipeMaterial);
	dynamicMeshComponent->SetRelativeRotation(rotation);
	dynamicMeshComponent->SetWorldLocation(localOffset);
}