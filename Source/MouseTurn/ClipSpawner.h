// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ClipSpawner.generated.h"

UCLASS()
class MOUSETURN_API AClipSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClipSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AClip> ClipBlueprint;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MaxSpawnDelay = 10.f;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MinSpawnDelay = 5.f;
    
    float CurrentSpawnDelay = 0.f;

	
	
};
