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

    /**What enemy should be spawned*/
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AEnemy> EnemyBlueprint;
    
    /**The maximum time before an enemy is spawned*/
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MaxSpawnDelay = 3.f;
    
    /**The minimum time before an enemy is spawned*/
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MinSpawnDelay = 1.f;
    
    //How long to next spawn
    float CurrentSpawnDelay = 0.f;
    
};
