// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InteractionComponent.h"
#include "Interfaces/Interactable.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

    Pawn = Cast<APawn>(GetOwner());
    if (!Pawn) return;

    PC = Cast<APlayerController>(Pawn->GetController());

    if (!PC)
    {
        return;
    }
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	UpdateInteractable();


}


void UInteractionComponent::UpdateInteractable()
{

    int32 ViewportX, ViewportY;
    PC->GetViewportSize(ViewportX, ViewportY);

    FVector WorldLocation;
    FVector WorldDirection;

    if (!PC->DeprojectScreenPositionToWorld(
        ViewportX * 0.5f,
        ViewportY * 0.5f,
        WorldLocation,
        WorldDirection))
    {
        return;
    }

    FVector Start = WorldLocation;
    FVector End = Start + WorldDirection * InteractionDistance;

    FHitResult Hit;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Pawn);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        Start,
        End,
        ECC_Visibility,
        Params
    );

    AActor* NewInteractable = nullptr;

    if (bHit)
    {
        AActor* HitActor = Hit.GetActor();

        if (HitActor && HitActor->Implements<UInteractable>())
        {
            NewInteractable = HitActor;
        }
    }

    if (NewInteractable == CurrentInteractable)
    {
        return;
    }

    if (CurrentInteractable)
    {
        UE_LOG(LogTemp, Warning, TEXT("UnHighlight"));

        UActorComponent* Highlightable =
            CurrentInteractable->FindComponentByInterface(UInteractable::StaticClass());

        IInteractable::Execute_UnHighlight(Highlightable);
    }

    CurrentInteractable = NewInteractable;

    if (CurrentInteractable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Highlight"));

        UActorComponent* Highlightable =
            CurrentInteractable->FindComponentByInterface(UInteractable::StaticClass());

        IInteractable::Execute_Highlight(Highlightable);
    }
}



void UInteractionComponent::Interaction()
{
    if (!CurrentInteractable)
    {
        return;
    }
    IInteractable::Execute_Interact(
        CurrentInteractable,
        GetOwner());
}

