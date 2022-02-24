// OEF

#include "Enemy.h"
#include "MouseTurn.h"
#include "MyPawn.h"

#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ///A standard box collider with Overlap Events:
    RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemy"));
    RootComponent = RootBox;
    RootBox->SetGenerateOverlapEvents(true);
    //Visual component added in blueprint
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
    ///Must cast a pawn to the correct type to set enemies shot
    ///Could have used GameMode or something else also to store this
    AMyPawn* TempPawn = Cast<AMyPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    TempPawn->EnemiesShot++;
    Destroy();
}

