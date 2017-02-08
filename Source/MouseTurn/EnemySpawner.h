// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class MOUSETURN_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AEnemy> EnemyBlueprint;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MaxSpawnDelay = 3.f;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MinSpawnDelay = 1.f;
    
    float CurrentSpawnDelay = 0.f;
    
};
