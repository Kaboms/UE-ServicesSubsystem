// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServicesSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogServicesSubsystem, Log, All);

class UServiceBase;

UCLASS(config = Game, defaultconfig)
class GAMEINSTANCESERVICES_API UServicesSubsystemSettings : public UObject
{
	GENERATED_BODY()

public:
	UServicesSubsystemSettings() {};

	static const UServicesSubsystemSettings* Get()
	{
		return GetDefault<UServicesSubsystemSettings>(UServicesSubsystemSettings::StaticClass());
	}

public:
	UPROPERTY(config, EditDefaultsOnly, Category = "Default")
	TArray<TSoftClassPtr<UServiceBase>> StartupServices;

	UPROPERTY(config, EditDefaultsOnly, Category = "Default")
	TMap<TSoftClassPtr<UServiceBase>, TSoftClassPtr<UServiceBase>> ServicesReferences;
};

/**
 * 
 */
UCLASS()
class GAMEINSTANCESERVICES_API UServicesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Return singleton service by type
	UFUNCTION(BlueprintCallable, Meta = (DeterminesOutputType = "ServiceClass"))
	UPARAM(DisplayName = "Service") UServiceBase*  GetService(TSubclassOf<UServiceBase> ServiceClass);

	UFUNCTION(BlueprintPure, DisplayName = "Get Service", Meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ServiceClass"))
	static UPARAM(DisplayName="Service") UServiceBase* K2_GetService(const UObject* WorldContextObject, TSubclassOf<UServiceBase> ServiceClass);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	virtual void Deinitialize() override;

	void OnGameInstanceStart(UGameInstance* GameInstance);

protected:
	UPROPERTY()
	TMap<TSubclassOf<UServiceBase>, TObjectPtr<UServiceBase>> Services;
};
