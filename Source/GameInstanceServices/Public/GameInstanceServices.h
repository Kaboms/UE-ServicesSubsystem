// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameInstanceServices, Log, All);

class FGameInstanceServicesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Settings
	void RegisterSettings();
	void UnregisterSettings();
	bool HandleSettingsSaved();
	// End of Settings
};
