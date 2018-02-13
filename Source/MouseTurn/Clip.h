// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Clip.generated.h"

class USphereComponent;

UCLASS()
class MOUSETURN_API AClip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClip();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    /**The collision shape of the clip*/
    UPROPERTY(EditAnywhere)
    USphereComponent* RootSphere = nullptr;
	
};
