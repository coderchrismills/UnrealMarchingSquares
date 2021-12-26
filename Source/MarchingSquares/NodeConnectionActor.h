// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeConnectionActor.generated.h"

UCLASS()
class MARCHINGSQUARES_API ANodeConnectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeConnectionActor();

	UPROPERTY(VisibleAnywhere)
	int32 isoValue = 0;

	UPROPERTY(VisibleAnywhere)
	UMaterialInterface* pipeMaterial = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMesh* dynamicMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateMesh(FRotator rotation, FVector localOffset);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Initialize(int32 iv);
};
