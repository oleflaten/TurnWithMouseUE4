// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawner.h"
#include "MouseTurn.h"
#include "Enemy.h"

#include "Components/SphereComponent.h"
#include "Engine/World.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    CurrentSpawnDelay -= DeltaTime;
    if (CurrentSpawnDelay < 0)
    {
        GetWorld()->SpawnActor<AEnemy>(EnemyBlueprint, GetActorLocation(), FRotator::ZeroRotator);
        CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
    }
}

