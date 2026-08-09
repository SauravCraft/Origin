#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OriginGameInstance.generated.h"

UCLASS()
class ORIGIN_API UOriginGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:

    virtual void Init() override;
    virtual void Shutdown() override;
};