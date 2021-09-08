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
		Modules.Init(Null);
	}
}

#include <index_macros_end>