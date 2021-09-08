#pragma once

#include "../InUI/Include.h"
#include <lib.horion.h>

#include <index_macros>

namespace Skid::Module
{
	struct UITestModule : IModule
	{
		UITestModule() : IModule(NULL, Category::CUSTOM, "Lol") { }
		fun getModuleName() -> const char* override { return "UITestModule"; }
	};
}

#include <index_macros_end>