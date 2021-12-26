// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"

#include "NodeActor.generated.h"

UCLASS()
class MARCHINGSQUARES_API ANodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeActor();

	UPROPERTY(VisibleAnywhere)
	bool isEnabled = false;

	UPROPERTY(VisibleAnywhere)
	UMaterialInterface* pineMaterial = nullptr;

	UPROPERTY(VisibleAnywhere)
	UMaterialInterface* walnutMaterial = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* dynamicMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMesh* dynamicMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(bool enabled);
};
