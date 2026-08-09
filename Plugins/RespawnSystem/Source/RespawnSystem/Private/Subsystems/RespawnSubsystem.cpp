#include "Subsystems/RespawnSubsystem.h"
#include "Actors/CheckpointBox.h"
#include "Subsystems/SaveManagerSubsystem.h"
#include "SaveGames/SaveGameData.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

void URespawnSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);


    if (USaveManagerSubsystem* Save =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>())
    {
       

        Save->OnGameSaved.AddUObject(
            this,
            &URespawnSubsystem::HandleSave);
        UE_LOG(LogTemp, Warning, TEXT("Binding Load Delegate"));
        Save->OnGameLoaded.AddUObject(
            this,
            &URespawnSubsystem::HandleLoad);

        UE_LOG(LogTemp, Warning, TEXT("Respawn Bound To Save Delegates"));



    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Save Subsystem NOT FOUND"));
    }
}

void URespawnSubsystem::Deinitialize()
{
    Super::Deinitialize();

    UE_LOG(LogTemp, Log, TEXT("Respawn Subsystem Deinitialized"));
}

void URespawnSubsystem::SetCheckpoint(const FTransform& Checkpoint)
{
    if (!Checkpoint.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Checkpoint Transform"));
        return;
    }
     
    // Avoid broadcasting if the checkpoint hasn't changed 

    if (CurrentCheckpoint.Equals(Checkpoint))
    {
        return;
    }

    CurrentCheckpoint = Checkpoint;

    UE_LOG(LogTemp, Warning,
        TEXT("Checkpoint Updated: %s"),
        *CurrentCheckpoint.GetLocation().ToString());

    USaveManagerSubsystem* SaveSubsystem =
        GetGameInstance()->GetSubsystem<USaveManagerSubsystem>();
    SaveSubsystem->SaveGame();


    OnCheckpointActivated.Broadcast(CurrentCheckpoint);
}






bool URespawnSubsystem::IsCheckpointActivated(FName CheckpointId) const
{
    return CurrentActiveCheckpoints.Contains(CheckpointId);
}

void URespawnSubsystem::ActivateCheckpoint(FName CheckpointId)
{
    CurrentActiveCheckpoints.AddUnique(CheckpointId);
}







bool URespawnSubsystem::RespawnPlayer(APawn* Pawn , const FTransform& SpawnTransform)
{
    UE_LOG(LogTemp, Warning, TEXT("Respawn System Call"));


    if (!Pawn)
    {
        return false;
    }

    AController* Controller = Pawn->GetController();

    if (!Controller)
    {
        return false;
    }

    UWorld* World = GetWorld();

    if (!World)
    {
        return false;
    }

    FVector SpawnLocation = SpawnTransform.GetLocation();
    FRotator SpawnRotation = SpawnTransform.GetRotation().Rotator();

    Controller->UnPossess();

    if (Pawn)
    {
        Pawn->SetActorHiddenInGame(true);
        Pawn->SetActorEnableCollision(false);
        Pawn->DisableInput(nullptr);
        Pawn->SetLifeSpan(0.1f);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    APawn* NewPawn = World->SpawnActor<APawn>(
        Pawn->GetClass(),
        SpawnLocation,
        SpawnRotation,
        SpawnParams);

    if (!NewPawn)
    {
        return false;
    }

    Controller->Possess(NewPawn);
    
    UE_LOG(LogTemp, Warning,
        TEXT("Pawn After Possess = %s"),
        *NewPawn->GetActorLocation().ToString());
    return true;
}



void URespawnSubsystem::HandleSave(USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        return;
    }

    SaveGame->CurrentCheckpointTransform =
        CurrentCheckpoint;
    SaveGame->ActiveCheckpoints =
        CurrentActiveCheckpoints;

    UE_LOG(LogTemp, Log,
        TEXT("Saved Checkpoint: %s"),
        *CurrentCheckpoint.GetLocation().ToString());

    UE_LOG(LogTemp, Log,
        TEXT("Active Checkpoints: %d"),
        CurrentActiveCheckpoints.Num());

    for (const FName& Checkpoint : CurrentActiveCheckpoints)
    {
        UE_LOG(LogTemp, Log,
            TEXT(" - %s"),
            *Checkpoint.ToString());
    }
}

void URespawnSubsystem::HandleLoad(USaveGameData* SaveGame)
{
    if (!SaveGame)
    {
        return;
    }

    CurrentCheckpoint =
        SaveGame->CurrentCheckpointTransform;
    CurrentActiveCheckpoints =
        SaveGame->ActiveCheckpoints;
    LoadedPlayerTransform =
        SaveGame->PlayerTransform;

    UE_LOG(LogTemp, Log,
        TEXT("Loaded Checkpoint: %s"),
        *CurrentCheckpoint.GetLocation().ToString());

    UE_LOG(LogTemp, Log,
        TEXT("Loaded Active Checkpoints: %d"),
        CurrentActiveCheckpoints.Num());

    for (const FName& Checkpoint : CurrentActiveCheckpoints)
    {
        UE_LOG(LogTemp, Log,
            TEXT(" - %s"),
            *Checkpoint.ToString());
    }

    OnCheckpointLoaded.Broadcast();
}