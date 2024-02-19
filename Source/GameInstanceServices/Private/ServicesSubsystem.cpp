// Fill out your copyright notice in the Description page of Project Settings.


#include "ServicesSubsystem.h"
#include "ServiceBase.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogServicesSubsystem)

#define LOCTEXT_NAMESPACE "ServicesSubsystem"

UServiceBase* UServicesSubsystem::GetService(TSubclassOf<UServiceBase> ServiceClass)
{
    UClass* NewServiceClass = ServiceClass;

    const UServicesSubsystemSettings* ServicesSubsystemSettings = UServicesSubsystemSettings::Get();
    const TSoftClassPtr<UServiceBase>* ServiceReference = ServicesSubsystemSettings->ServicesReferences.Find(*ServiceClass);
    if (ServiceReference)
    {
        NewServiceClass = ServiceReference->LoadSynchronous();
    }

    if (Services.Contains(NewServiceClass))
    {
        return Services[NewServiceClass];
    }

    UServiceBase* Service = NewObject<UServiceBase>(this, NewServiceClass, NewServiceClass->GetFName());
    Service->Init();
    Services.Add(NewServiceClass, Service);

    return Service;
}

UServiceBase* UServicesSubsystem::K2_GetService(const UObject* WorldContextObject, TSubclassOf<UServiceBase> ServiceClass)
{
    UServicesSubsystem* ServicesSubsystem = UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UServicesSubsystem>();
    if (IsValid(ServicesSubsystem))
    {
        return ServicesSubsystem->GetService(ServiceClass);;
    }

    return nullptr;
}

void UServicesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FWorldDelegates::OnStartGameInstance.AddUObject(this, &UServicesSubsystem::OnGameInstanceStart);
}

void UServicesSubsystem::Deinitialize()
{
    TArray<TObjectPtr<UServiceBase>> ServicesArray;
    Services.GenerateValueArray(ServicesArray);

    for (UServiceBase* Service : ServicesArray)
    {
        Service->Deinitialize();
    }
}

void UServicesSubsystem::OnGameInstanceStart(UGameInstance* GameInstance)
{
    const UServicesSubsystemSettings* ServicesSubsystemSettings = UServicesSubsystemSettings::Get();
    for (TSoftClassPtr<UServiceBase> ServiceClassPtr : ServicesSubsystemSettings->StartupServices)
    {
        UClass* ServiceClass = ServiceClassPtr.LoadSynchronous();
        if (IsValid(ServiceClass))
        {
            UE_LOG(LogServicesSubsystem, Log, TEXT("Create default service: %s"), *ServiceClass->GetFName().ToString());

            GetService(ServiceClass);
        }
    }

    for (auto ServiceItem : Services)
    {
        ServiceItem.Value->PostStartup();
    }
}
#undef LOCTEXT_NAMESPACE
