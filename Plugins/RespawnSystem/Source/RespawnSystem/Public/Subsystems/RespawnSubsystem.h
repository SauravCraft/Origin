#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RespawnSubsystem.generated.h"

class APawn;
class USaveGameData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCheckpointActivated, FTransform);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerRespawned, APawn*);
DECLARE_MULTICAST_DELEGATE(FOnCheckpointLoaded);

UCLASS()
class RESPAWNSYSTEM_API URespawnSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Set active checkpoint */
    void SetCheckpoint(const FTransform& Checkpoint);

    /** Respawn an existing pawn */
    bool RespawnPlayer(APawn* Player, const FTransform& SpawnTransform);

    /** Current checkpoint */
    FORCEINLINE FTransform GetCurrentCheckpoint() const
    {
        return CurrentCheckpoint;
    }

    // Getter for Active Checkpoints

    bool IsCheckpointActivated(FName CheckpointId) const;

    void ActivateCheckpoint(FName CheckpointId);

    FTransform LoadedPlayerTransform;

    // Save System 

    UFUNCTION()
    void HandleSave(USaveGameData* SaveGame);

    UFUNCTION()
    void HandleLoad(USaveGameData* SaveGame);


    //  Delegates 

    FOnCheckpointActivated OnCheckpointActivated;
    FOnPlayerRespawned OnPlayerRespawned;
    FOnCheckpointLoaded OnCheckpointLoaded;


private:

    UPROPERTY()
    FTransform CurrentCheckpoint;

    UPROPERTY()
    TArray<FName> CurrentActiveCheckpoints;
    

};