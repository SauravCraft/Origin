#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "OriginCharacter.generated.h"

class UInputAction;
class USaveGameData;

UCLASS(Blueprintable)
class ORIGIN_API AOriginCharacter : public APawn
{
	GENERATED_BODY()

public:
	AOriginCharacter();


protected:

	/** Root Capsule */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;


	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void HandleSave(USaveGameData* SaveGame);

	UFUNCTION()
	void HandleLoad(USaveGameData* SaveGame);

	UFUNCTION()
	void HandleDeath();




	// Input Function

	UFUNCTION(BlueprintCallable)
	void SaveGameTest();

	UFUNCTION(BlueprintCallable)
	void LoadGameTest();

	UFUNCTION(BlueprintCallable)
	void TakeDamageTest();

	UFUNCTION(BlueprintCallable)
	void interact();

	// Input Actions 


	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LoadAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SaveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* TakeDamage;



};