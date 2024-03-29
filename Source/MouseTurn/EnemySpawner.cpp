// OEF

#include "EnemySpawner.h"
#include "MouseTurn.h"
#include "Enemy.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ///No collider - only visible mesh
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    ///Set up the visual component - the actual mesh is set in Blueprint
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
    OurVisibleComponent->SetupAttachment(RootComponent);
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
        ///Random time till next spawn
        CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
    }
}
