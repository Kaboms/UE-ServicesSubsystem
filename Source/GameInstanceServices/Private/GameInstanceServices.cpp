// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameInstanceServices.h"
#include "ServicesSubsystem.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#endif

#define LOCTEXT_NAMESPACE "FGameInstanceServicesModule"

IMPLEMENT_MODULE(FGameInstanceServicesModule, SharedLibrary)

DEFINE_LOG_CATEGORY(LogGameInstanceServices)

void FGameInstanceServicesModule::StartupModule()
{
    RegisterSettings();
}

void FGameInstanceServicesModule::ShutdownModule()
{
}

void FGameInstanceServicesModule::RegisterSettings()
{
#if WITH_EDITOR
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

    if (SettingsModule)
    {
        SettingsModule->RegisterSettings("Project", "Game", "ServicesSubsystemSettings",
            LOCTEXT("RuntimeGameSettingsName", "Services Subsystem Settings"),
            LOCTEXT("RuntimeGameSettingsDescription", "Configure services subsystem settings"),
            GetMutableDefault<UServicesSubsystemSettings>()
        );
    }
#endif
}

void FGameInstanceServicesModule::UnregisterSettings()
{
}

bool FGameInstanceServicesModule::HandleSettingsSaved()
{
    return false;
}
#undef LOCTEXT_NAMESPACE