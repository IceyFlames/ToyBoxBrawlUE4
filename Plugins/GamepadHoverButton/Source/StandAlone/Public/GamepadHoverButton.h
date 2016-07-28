#pragma once

#include "ModuleManager.h"

class GamepadHoverButtonImpl : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	void StartupModule();
	void ShutdownModule();
};