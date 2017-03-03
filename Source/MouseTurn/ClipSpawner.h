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
    
    /**What the spawner should spawn*/
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AClip> ClipBlueprint;
    
    /**The maximum time before a clip is spawned*/
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MaxSpawnDelay = 10.f;
    
    /**The minimum time before a clip is spawned*/
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float MinSpawnDelay = 5.f;
    
    //How long to next spawn
    float CurrentSpawnDelay = 0.f;

	
	
};
