// OEF

#include "Bullet.h"
#include "MouseTurn.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    //Collision object and RootObject
    RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BulletCollider"));
    RootComponent = RootSphere;
    RootSphere->SetGenerateOverlapEvents(true);
    RootSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

    ///Set up the visual component - the actual mesh is set in Blueprint
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
    OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    FVector NewLocation = GetActorLocation();
    NewLocation += GetActorForwardVector() * Speed * DeltaTime;
    SetActorLocation(NewLocation);
    
    TimeLived += DeltaTime;
    if (TimeLived > TimeBeforeDestroy)
    {
        this->Destroy();
    }
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
                        UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult &SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap %s"), *OtherActor->GetName())
    if(OtherActor->IsA(AEnemy::StaticClass()))
    {
        Cast<AEnemy>(OtherActor)->ImHit(); //Alternativt bare OtherActor->Destroy();
        
        //Destroy Bullet:
        Destroy();
    }
}

