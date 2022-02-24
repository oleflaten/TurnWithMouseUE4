// OEF

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UDecalComponent;
class UShapeComponent;
class USceneComponent;
class ABullet;

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
    
    //Input functions
    void Move_XAxis(float AxisValue);
    void Move_YAxis(float AxisValue);
    void Shoot();
    void StartShooting();
    void StopShooting();
    void Restart();
    bool DoTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams);
    
    /**How much ammo does the pawn have now*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Setup")
    int Ammo = 20;
    
    /**How many enemies have the pawn shot*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Setup")
    int EnemiesShot = 0;
    
private:
    UPROPERTY(EditAnywhere, Category = "Pawn Setup")
    USceneComponent* OurVisibleComponent;
    
    /**The max movement speed of the pawn*/
    UPROPERTY(EditAnywhere, Category = "Pawn Setup")
    int Speed = 100;

    /**How fast is the autoshoot?*/
    UPROPERTY(EditAnywhere, Category = "Pawn Setup")
    float ShootSpeed = 0.3f;
    
    /**The speed of pawn rotation*/
    UPROPERTY(EditAnywhere, Category = "Pawn Setup")
    float YawSpeed = 0.3f;
    
    /**The bullet the pawn shoots*/
    UPROPERTY(EditAnywhere, Category = "Pawn Setup")
    TSubclassOf<ABullet> BulletBlueprint;
    
    /**How much ammo does the pawn get from clips*/
    UPROPERTY(EditAnywhere, Category = "Pawn Setup")
    int AmmoInClip = 20;
    
    /** A decal that projects to the cursor location. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Setup", meta = (AllowPrivateAccess = "true"))
    UDecalComponent* CursorToWorld;
    
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
 
    /**Holds whether the pawn is dead or not*/
    bool Died = false;
    /** The velocity of the pawn*/
    FVector CurrentVelocity;
    /**Is the pawn shooting*/
    bool IsShooting;
    /**Collision shape*/
    UShapeComponent* CollisionBox = nullptr;
    /** How long time to next shot*/
    float NextShot = -0.1f;
 

    
    
    
};
