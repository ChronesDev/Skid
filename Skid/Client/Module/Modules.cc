#include "AllModules.h"

#include <index>
#include <lib.horion.h>

#include <index_macros>

namespace Skid
{
	using namespace Index;

	inline struct SkidModules
	{
	private:
		ModuleManager* Manager_;

	public:
		fun Init(Nullable<ModuleManager&> modManager)
		{
			var m = modManager.ValueOr(moduleMgr);
			Manager_ = &m;
		}

		fun TryAddModule(IPtr<IModule> m)
		{
			if (!Manager_) throw ".";


		}

		fun AddDefaultModules()
		{
			if (!Manager_) throw ".";
		}
	}
	Modules;
}

#include <index_macros_end>