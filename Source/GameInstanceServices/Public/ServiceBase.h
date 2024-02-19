// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ServiceBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GAMEINSTANCESERVICES_API UServiceBase : public UObject
{
	GENERATED_BODY()

public:
	// Called when service is constructed
	virtual void Init();

	// Called when all Startup Services is initialized
	virtual void PostStartup();

	virtual void Deinitialize();

	UGameInstance* GetGameInstance();

	virtual class UWorld* GetWorld() const override;

protected:
	// Called when service is constructed
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Init"))
	void ReceiveInit();

	// Called when all Startup Services is initialized
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Post Startup"))
	void ReceivePostStartup();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Deinitialize"))
	void ReceiveDeinitialize();

protected:
	TObjectPtr<class UServicesSubsystem> ServicesSubsystem;
};
