#pragma once

#include "../../Utils.h"

#include <index_macros>

namespace Skid::InUI
{
	struct FillRect : virtual UIElement
	{
		Index::Color Color = Colors::White;
		float Alpha = 1.f;
		INDEX_UI_Args{
			INDEX_UI_DefaultMembers
			Index::Color Color = Colors::White;
			float Alpha = 1.f;
		};
		INDEX_UI_New(FillRect)
		INDEX_UI_Constructor(FillRect) {
			INDEX_UI_SetDefaultMembers
			Color = e.Color;
			Alpha = e.Alpha;
		}
		void Render(UIContext* u, Layout i) override
		{
			var r = GetSubrect(this, i);
			DrawUtils::fillRectangle(FromVec4({ r.X, r.Y, r.Second.X, r.Second.Y }), FromColor(Color), Alpha);
		}
	};
}

#include <index_macros_end>