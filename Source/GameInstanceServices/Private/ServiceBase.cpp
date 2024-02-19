// Fill out your copyright notice in the Description page of Project Settings.


#include "ServiceBase.h"
#include "ServicesSubsystem.h"

void UServiceBase::Init()
{
    ServicesSubsystem = Cast<UServicesSubsystem>(GetOuter());

	UE_LOG(LogServicesSubsystem, Log, TEXT("Service init: %s"), *GetFName().ToString());

    ReceiveInit();
}

void UServiceBase::PostStartup()
{
	UE_LOG(LogServicesSubsystem, Log, TEXT("Service post startup: %s"), *GetFName().ToString());

	ReceivePostStartup();
}

void UServiceBase::Deinitialize()
{
	UE_LOG(LogServicesSubsystem, Log, TEXT("Service deinitialize: %s"), *GetFName().ToString());

    ReceiveDeinitialize();
}

UGameInstance* UServiceBase::GetGameInstance()
{
    return ServicesSubsystem->GetGameInstance();
}

UWorld* UServiceBase::GetWorld() const
{
	if (GetOuter() == nullptr)
	{
		return nullptr;
	}

	// Special case for behavior tree nodes in the editor
	if (Cast<UPackage>(GetOuter()) != nullptr)
	{
		// GetOuter should return a UPackage and its Outer is a UWorld
		return Cast<UWorld>(GetOuter()->GetOuter());
	}

	// In all other cases...
	return GetOuter()->GetWorld();
}
