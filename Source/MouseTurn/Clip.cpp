// Fill out your copyright notice in the Description page of Project Settings.

#include "Clip.h"
#include "MouseTurn.h"

#include "Components/SphereComponent.h"


// Sets default values
AClip::AClip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ClipSphere"));
    RootSphere->SetSphereRadius(80.f);
    RootComponent = RootSphere;
    RootSphere->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AClip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    AddActorLocalRotation(FRotator(0.0f, 0.0f, 50.0f)*DeltaTime);
}

