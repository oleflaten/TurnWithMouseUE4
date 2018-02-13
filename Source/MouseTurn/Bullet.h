// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UShapeComponent;

UCLASS()
class MOUSETURN_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
private:
    /**Speed of bullet*/
    UPROPERTY(EditAnywhere)
    float Speed = 400.f;
    
    /**Time before bullet selfdestruct*/
    UPROPERTY(EditAnywhere)
    float TimeBeforeDestroy = 5.f;
    
    float TimeLived{0};
    
    /**The collision shape of the bullet*/
    UPROPERTY(EditAnywhere)
    UShapeComponent* RootSphere = nullptr;

    
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
                   UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
                   bool bFromSweep, const FHitResult &SweepResult);

	
	
};
