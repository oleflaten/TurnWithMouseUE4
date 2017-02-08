// Fill out your copyright notice in the Description page of Project Settings.

#include "MouseTurn.h"
#include "Enemy.h"
#include "MyPawn.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemy"));
    RootComponent = RootBox;
    RootBox->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
    MoveDirection.Normalize();
    SetActorRotation(MoveDirection.Rotation());
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    FVector NewLocation = GetActorLocation();
    NewLocation += (MoveDirection * Speed * DeltaTime);
    SetActorLocation(NewLocation);
    
    CurrentTurnDelay -= DeltaTime;
    ///Turns the enemy after some time:
    if (CurrentTurnDelay < 0.f)
    {
        MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
        MoveDirection.Normalize();
        SetActorRotation(MoveDirection.Rotation());
    
        CurrentTurnDelay = FMath::FRandRange(TurnDelayMin, TurnDelayMax);
    }
}

void AEnemy::ImHit()
{
    AMyPawn* TempPawn = Cast<AMyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    TempPawn->EnemiesShot++;
    Destroy();
}

