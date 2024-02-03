// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketPlayerController.h"
#include "WebSocketsModule.h"

void ASocketPlayerController::BeginPlay()
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
}

void ASocketPlayerController::EndPlay()
{
    Super::EndPlay();

    if (Socket->IsConnected())
    {
        Socket->Close();
    }
}