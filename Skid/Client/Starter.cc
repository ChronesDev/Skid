#pragma once

#include "../InUI/Include.h"
#include <lib.horion.h>

#include "Module/Modules.cc"

#include <index_macros>

namespace Skid
{
	using namespace Index;

	global fun Start()
	{
		moduleMgr->getModuleList()->push_back(INew<Module::SdAutoArmor>().DynamicAs<IModule>());

		Sleep(10);

		cmdMgr->initCommands();
		moduleMgr->initModules();
		configMgr->init();

		Sleep(10);

		Hooks::Enable();
		TabGui::init();
		ClickGui::init();
	}
}

#include <index_macros_end>