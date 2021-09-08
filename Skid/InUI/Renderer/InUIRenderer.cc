#pragma once

#include "../Utils.h"

#include <index_macros>

namespace Skid::InUI
{
	struct HorionRenderer : UI::UIContext
	{
	private:
		static bool IsRendering;
	public:
		static GameData* CurrentGameData;
		static C_GuiData* CurrentGuiData;

		fun Render(GameData* gameData)
		{
			if (IsRendering) throw "Cannot start rendering while Rendering.";
			if (Root.IsNull) throw "Root is null.";
			if (gameData == nullptr) throw "GameData is null.";
			IsRendering = true;
			CurrentGameData = gameData;
			CurrentGuiData = gameData->getGuiData();
			Root->Render(nullptr, {
				.Area = Rect(0, 0, ToVec2(CurrentGuiData->windowSize))
			});
			CurrentGameData = nullptr;
			CurrentGuiData = nullptr;
			IsRendering = false;
		}

		fun Notify(Index::UI::UINotification *e) -> void override
		{
			if (Root.IsNull) throw "Root is null.";
			Root->Notify(e);
		}
	};
}

#include <index_macros_end>