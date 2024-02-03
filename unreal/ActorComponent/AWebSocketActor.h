// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IWebSocket.h" // Socket definition
#include "AWebSocketActor.generated.h"

UCLASS()
class SHOOTERSOCKETTEST_API AAWebSocketActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAWebSocketActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    int frameEven = 0;
    bool flip = false;

    FVector startingLocation;

    TSharedPtr<IWebSocket> Socket;
};
