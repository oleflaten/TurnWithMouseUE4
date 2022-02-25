// OEF

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

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

    /**The collision shape of the bullet*/
    UPROPERTY(EditAnywhere, Category = "Bullet")
        class USphereComponent* RootSphere{nullptr};

    UPROPERTY(VisibleAnywhere, Category = "Bullet")
        class UStaticMeshComponent* OurVisibleComponent { nullptr };

private:
    /**Speed of bullet*/
    UPROPERTY(EditAnywhere, Category = "Bullet")
        float Speed{400.f};
    
    /**Time before bullet selfdestruct*/
    UPROPERTY(EditAnywhere, Category = "Bullet")
        float TimeBeforeDestroy{5.f};
    
    float TimeLived{0};
    
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
                   UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
                   bool bFromSweep, const FHitResult &SweepResult);
};
