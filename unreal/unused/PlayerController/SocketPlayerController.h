// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IWebSocket.h" // Socket definition
#include "SocketPlayerController.generated.h"

/**
 *
 */
UCLASS()
class WEBSOCKETTEST1_API ASocketPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    virtual void EndPlay() override;

    TSharedPtr<IWebSocket> Socket;
};
