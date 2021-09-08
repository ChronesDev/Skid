#pragma once

#include <index>
#include <index_ui>
#include <lib.horion.h>

#include <index_macros>

namespace Skid::InUI
{
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
}

#include <index_macros_end>