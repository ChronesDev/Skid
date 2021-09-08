#pragma once

#include <index>
#include <index_ui>
#include <lib.horion.h>

#include <index_macros>

namespace Skid::InUI
{
	using namespace Index;
	using namespace Index::UI;

	global fun ToVec2(vec2_t v) -> Index::Vec2F
	{
		return Index::Vec2F(v.x, v.y);
	}

	global fun ToVec3(vec3_t v) -> Index::Vec3F
	{
		return Index::Vec3F(v.x, v.y, v.z);
	}

	global fun ToVec4(vec4_t v) -> Index::Vec4F
	{
		return Index::Vec4F(v.x, v.y, v.z, v.w);
	}

	global fun FromVec2(Vec2F v) -> vec2_t
	{
		return vec2_t(v.X, v.Y);
	}

	global fun FromVec3(Vec3F v) -> vec3_t
	{
		return vec3_t(v.X, v.Y, v.Z);
	}

	global fun FromVec4(Vec4F v) -> vec4_t
	{
		return vec4_t(v.X, v.Y, v.Z, v.W);
	}

	global fun ToColor(MC_Color c) -> Color
	{
		return Color::Raw({ c.r, c.g, c.b, c.a });
	}

	global fun FromColor(Color c) -> MC_Color
	{
		var v = c.AsRawVec();
		return MC_Color(v.X, v.Y, v.Z, v.W);
	}
}

#include <index_macros_end>