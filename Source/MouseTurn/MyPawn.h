// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class MOUSETURN_API AMyPawn : public APawn
{
    GENERATED_BODY()
    
public:
    // Sets default values for this pawn's properties
    AMyPawn();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    //void RotateWithMouse();
    
    //Input functions
    void Move_XAxis(float AxisValue);
    void Move_YAxis(float AxisValue);
    void Shoot();
    void StartShooting();
    void StopShooting();
    void Restart();
    bool DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams);
    
    //Input variables
    FVector CurrentVelocity;
    bool IsShooting;
    
    UPROPERTY(EditAnywhere)
    USceneComponent* OurVisibleComponent;
    
    UPROPERTY(EditAnywhere)
    int Speed = 100;

    UPROPERTY(EditAnywhere)
    float ShootSpeed = 0.3f;
    
    UPROPERTY(EditAnywhere)
    float YawSpeed = 0.3f;
    
    UPROPERTY(EditAnywhere, Category="Spawning")
    TSubclassOf<class ABullet> BulletBlueprint;
    
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
 
    bool Died = false;
    
    UShapeComponent* CollisionBox = nullptr;
        
    float NextShot = -0.1f;
 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    int Ammo = 20;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    int EnemiesShot = 0;

    UPROPERTY(EditAnywhere)
    int AmmoInClip = 20;
    
    
    
};
