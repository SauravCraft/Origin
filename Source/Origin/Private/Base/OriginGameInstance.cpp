#include "Base/OriginGameInstance.h"
#include "Subsystems/SaveManagerSubsystem.h"

void UOriginGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("Origin GameInstance Initialized"));

    if (USaveManagerSubsystem* SaveSubsystem =
        GetSubsystem<USaveManagerSubsystem>())
    {
        SaveSubsystem->LoadGame();
    }
}
void UOriginGameInstance::Shutdown()
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance Shutdown Start"));

    if (USaveManagerSubsystem* Save = GetSubsystem<USaveManagerSubsystem>())
    {
        UE_LOG(LogTemp, Warning, TEXT("Calling SaveGame"));
        Save->SaveGame();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("SaveSubsystem NULL"));
    }

    Super::Shutdown();
}