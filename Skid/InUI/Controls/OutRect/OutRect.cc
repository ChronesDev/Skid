#pragma once

#include "../../Utils.h"

#include <index_macros>

namespace Skid::InUI
{
	struct OutRect : virtual UIElement
	{
		Index::Color Color = Colors::White;
		float Alpha = 1.f;
		float LineWidth = 1.f;
		INDEX_UI_Args{
			INDEX_UI_DefaultMembers
			Index::Color Color = Colors::White;
			float Alpha = 1.f;
			float LineWidth = 1.f;
		};
		INDEX_UI_New(OutRect)
		INDEX_UI_Constructor(OutRect) {
			INDEX_UI_SetDefaultMembers
			Color = e.Color;
			Alpha = e.Alpha;
			LineWidth = e.LineWidth;
		}
		void Render(UIContext* u, Layout i) override
		{
			var r = GetSubrect(this, i);
			DrawUtils::drawRectangle(FromVec4({ r.X, r.Y, r.Second.X, r.Second.Y }), FromColor(Color), Alpha, LineWidth);
		}
	};
}

#include <index_macros_end>