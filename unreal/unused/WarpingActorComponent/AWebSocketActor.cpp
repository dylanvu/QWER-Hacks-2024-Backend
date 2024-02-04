// Fill out your copyright notice in the Description page of Project Settings.

#include "AWebSocketActor.h"
#include "WebSocketsModule.h"

// Sets default values
AAWebSocketActor::AAWebSocketActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAWebSocketActor::BeginPlay()
{
    Super::BeginPlay();
    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    Socket = FWebSocketsModule::Get().CreateWebSocket("ws://localhost:3001");

    // event handlers
    Socket->OnConnected().AddLambda([]()
                                    { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully Connected"); });

    Socket->OnConnectionError().AddLambda([](const FString &Error)
                                          { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error); });

    Socket->Connect();

    startingLocation = GetActorLocation();
}

// Called every frame
void AAWebSocketActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // print out the world location
    FVector location = GetActorLocation();
    // Convert the FVector to a FString for display
    FString LocationString = FString::Printf(TEXT("Actor Location: X=%.2f, Y=%.2f, Z=%.2f"), location.X, location.Y, location.Z);
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, LocationString);

    int offset = 0;
    // gonna do a funny little teleportation as a test
    if (frameEven % 1000 == 0)
    {
        flip = !flip;
    }
    else
    {
        frameEven++;
    }

    if (flip)
    {
        offset = 100;
    }
    SetActorLocation(FVector(startingLocation.X + offset, startingLocation.Y, startingLocation.Z));
}

void AAWebSocketActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (Socket->IsConnected())
    {
        Socket->Close();
    }
}