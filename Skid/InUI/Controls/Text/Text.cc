#pragma once

#include "../../Utils.h"

#include <index_macros>

namespace Skid::InUI
{
	struct Text : virtual UIElement
	{
		string Text_;
		Index::Color Color = Colors::White;
		float FontSize = 1.f;
		float Alpha = 1.f;
		Fonts Style = Fonts::DEFAULT;
		INDEX_UI_Args{
			INDEX_UI_DefaultMembers
			string Text;
			Index::Color Color = Colors::White;
			float FontSize = 1.f;
			float Alpha = 1.f;
			Fonts Style = Fonts::DEFAULT;
		};
		INDEX_UI_New(Text)
		INDEX_UI_Constructor(Text){
			INDEX_UI_SetDefaultMembers
			Text_ = e.Text;
			Color = e.Color;
			FontSize = e.FontSize;
			Alpha = e.Alpha;
			Style = e.Style;
		}
		void Render(UIContext* u, Layout i) override
		{
			var r = GetSubrect(this, i);
			DrawUtils::drawText(FromVec2(r.First), &Text_, FromColor(Color), FontSize, Alpha, Style);
		}
		Index::Size MeasureIntentSize(Layout i) override
		{
			return Max(GetMinSize(this), {
				DrawUtils::getTextWidth(&Text_, FontSize, Style),
				DrawUtils::getFontHeight(FontSize, Style)
			});
		}
	};
}

#include <index_macros_end>