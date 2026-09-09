#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

UCLASS()
class SAVESYSTEM_API USaveGameData : public USaveGame
{
    GENERATED_BODY()

public:

    USaveGameData();

    /** Player */
    UPROPERTY(BlueprintReadWrite)
    FVector PlayerLocation;

    UPROPERTY(BlueprintReadWrite)
    FRotator PlayerRotation;

    /** Current Respawn Checkpoint */
    UPROPERTY(BlueprintReadWrite)
    FName CurrentCheckpoint;

    UPROPERTY()
    FTransform PlayerTransform;


    UPROPERTY(BlueprintReadWrite)
    FTransform CurrentCheckpointTransform;

    /** Activated Checkpoints */
    UPROPERTY(BlueprintReadWrite)
    TArray<FName> ActiveCheckpoints;

    /* Health System */
    UPROPERTY(BlueprintReadWrite)
    float CurrentHealth;

    /** Save Slot */
    UPROPERTY(BlueprintReadWrite)
    FString SlotName;

    UPROPERTY(BlueprintReadWrite)
    int32 UserIndex;
};