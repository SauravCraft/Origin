// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class USaveGameData;

DECLARE_MULTICAST_DELEGATE(FOnHealthChanged);
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE(FOnHeal);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEALTHSYSTEM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(AActor* Damagable, const float& Damage);

	UFUNCTION(BlueprintCallable)
	void Kill();

	UFUNCTION()
	void HandleSave(USaveGameData* SaveGame);

	UFUNCTION()
	void HandleLoad(USaveGameData* SaveGame);








	FOnHealthChanged OnHealthChange;
	FOnDeath OnDeath;
	FOnHeal OnHeal;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY()
	float CurrentHealth;



		
};
