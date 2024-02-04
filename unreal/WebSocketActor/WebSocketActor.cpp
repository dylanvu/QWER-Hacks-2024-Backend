// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocketActor.h"
#include "WebSocketsModule.h"
#include "JsonUtilities.h"

// Sets default values
AWebSocketActor::AWebSocketActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWebSocketActor::BeginPlay()
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

    Socket->OnMessage().AddLambda([this](const FString &MessageString)
                                  {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, MessageString);

			// Initialize a TSharedPtr to hold the output JSON object
			TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

			// Deserialize the string into the JSON object
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(MessageString);

			if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
			{
				// Successfully converted string to JSON
				// Now you can work with the JsonObject
				FString Value;
				if (JsonObject->TryGetStringField("shoot", Value))
				{
					// Access the value of the "shoot" field
					if (Value == "true") {
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "FIRE!");
						//Fire();
					}
				}
			}
			else
			{
				// Failed to convert string to JSON
				UE_LOG(LogTemp, Error, TEXT("Failed to convert string to JSON"));
			} });

    Socket->Connect();
}

// Called every frame
void AWebSocketActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWebSocketActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Socket->IsConnected())
    {
        Socket->Close();
    }
}