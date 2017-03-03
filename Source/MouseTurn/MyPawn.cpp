// Fill out your copyright notice in the Description page of Project Settings.

#include "MouseTurn.h"
#include "MyPawn.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Clip.h"


// Sets default values
AMyPawn::AMyPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    // Set this pawn to be controlled by the lowest-numbered player
    //Er satt opp i GameMode-blueprint
    //AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));

    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
    OurVisibleComponent->SetupAttachment(RootComponent);
    
    // Create a decal in the world to show the cursor's location
    CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
    CursorToWorld->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
    if (DecalMaterialAsset.Succeeded())
    {
        CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
    }
    CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
    CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
    Super::BeginPlay();

    //Show system cursor. Should probably be false
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
    
    //Set up collision shape
    CollisionBox = this->FindComponentByClass<UBoxComponent>();
    //CollisionBox->bGenerateOverlapEvents = true;
    
    if (CollisionBox)
    {
        CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnOverlap);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
    }
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    ///Auto shoot:
    if (IsShooting)
    {
        NextShot -= DeltaTime;
        if(NextShot <= 0.f)
        {
            Shoot();
            NextShot = ShootSpeed;
        }
    }
    else
    {
        NextShot = -0.1f;
    }
    
    /// Handle movement based on our "MoveX" and "MoveY" axes
    if (!CurrentVelocity.IsZero())
    {
        FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(Speed * DeltaTime);
        SetActorLocation(NewLocation);
    }
    
    
    /// Move the cursor
    FHitResult Hit;
    bool HitResult = false;
    
    HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);
    
    if (HitResult)
    {
        FVector CursorFV = Hit.ImpactNormal;
        FRotator CursorR = CursorFV.Rotation();
        CursorToWorld->SetWorldLocation(Hit.Location);
        CursorToWorld->SetWorldRotation(CursorR);

        ///Set the new direction of the pawn:
        FVector CursorLocation = Hit.Location;
        UE_LOG(LogTemp, Warning, TEXT("Hit location %s!"), *Hit.Location.ToString());
        FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y,  30.f);
        
        FVector NewDirection =  TempLocation - GetActorLocation();
        NewDirection.Z = 0.f;
        NewDirection.Normalize();
        SetActorRotation(NewDirection.Rotation());
    }
    
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
    
    // Respond when our "Grow" key is pressed or released.
    InputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPawn::StartShooting);
    InputComponent->BindAction("Shoot", IE_Released, this, &AMyPawn::StopShooting);
    InputComponent->BindAction("Restart", IE_Pressed, this, &AMyPawn::Restart).bExecuteWhenPaused = true;
    
    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
    InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
    // Move at 100 units per second forward or backward
    CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
    // Move at 100 units per second right or left
    CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Shoot()
{
    ///Spawn one bullet if we have ammo
    if (Ammo >0)
    {
        GetWorld()->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + GetActorForwardVector() * 100.f,
                                        GetActorRotation());
        Ammo--;
    }
}

void AMyPawn::StartShooting()
{
    IsShooting = true;
}

void AMyPawn::StopShooting()
{
    IsShooting = false;
}

void AMyPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if(OtherActor->IsA(AEnemy::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Died"))
        Died = true;
        this->SetActorHiddenInGame(true);
        UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
    if(OtherActor->IsA(AClip::StaticClass()))
    {
        Ammo = AmmoInClip;
        UE_LOG(LogTemp, Warning, TEXT("Player Picked Up Clip"))
        OtherActor->Destroy();
    }
}

void AMyPawn::Restart()
{
    if (Died)
    {
        UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
    }
}
