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
		fun Init(Nullable<ModuleManager*> modManager)
		{
			var m = modManager.ValueOr(moduleMgr);
			Manager_ = m;
		}

		fun ForceAddModule(IPtr<IModule> m)
		{
			if (!Manager_) throw std::exception(".");

			var lock = Manager_->lockModuleList();
			Manager_->getModuleList()->push_back(m);
		}

		fun AddDefaultModules()
		{
			if (!Manager_) throw std::exception(".");

			ForceAddModule(INew<Module::UITestModule>().As<IModule>());
			ForceAddModule(INew<Module::SdAutoArmor>().As<IModule>());
		}
	}
	Modules;
}

#include <index_macros_end>