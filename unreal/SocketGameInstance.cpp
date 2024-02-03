// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketGameInstance.h"
#include "WebSocketsModule.h"

void USocketGameInstance::Init()
{
    Super::Init();

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

void USocketGameInstance::Shutdown()
{
    Super::Shutdown();

    if (Socket->IsConnected())
    {
        Socket->Close();
    }
}