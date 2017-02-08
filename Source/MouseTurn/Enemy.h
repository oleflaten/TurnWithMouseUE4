// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class MOUSETURN_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    FVector MoveDirection = FVector(1.f, 0.f, 0.f);
    
    void ImHit();
    
    //AGameModeBase *GameModePointer;
    
    //int PlaceInArray{0};
    
private:
    UPROPERTY(EditAnywhere)
    float Speed = 150.f;
    
    UPROPERTY(EditAnywhere)
    float TurnDelayMax = 5.f;
    UPROPERTY(EditAnywhere)
    float TurnDelayMin = 1.f;
    
    float CurrentTurnDelay = 0.f;
    
    UPROPERTY(EditAnywhere)
    UShapeComponent* RootBox = nullptr;
};
