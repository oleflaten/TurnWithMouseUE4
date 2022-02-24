// OEF

#include "ClipSpawner.h"
#include "MouseTurn.h"
#include "Clip.h"

#include "Engine/World.h"

// Sets default values
AClipSpawner::AClipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClipSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AClipSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    CurrentSpawnDelay -= DeltaTime;
    if (CurrentSpawnDelay < 0)
    {
        GetWorld()->SpawnActor<AClip>(ClipBlueprint, GetActorLocation(), FRotator::ZeroRotator);
        CurrentSpawnDelay = FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay);
    }
}

