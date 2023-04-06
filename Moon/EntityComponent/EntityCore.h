#pragma once

#include <bitset>
#include <array>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>

#include <DirectXMath.h>
using namespace DirectX;

#include <DirectXPackedVector.h>
using namespace DirectX::PackedVector;

namespace ComponentBase
{
	static std::size_t GetUniqueComponentTypeID()
	{
		static std::size_t lastID = 0;
		return lastID++;
	}

	template<typename T>
	static std::size_t GetComponentTypeID() noexcept
	{
		static std::size_t typeID = GetUniqueComponentTypeID();
		return typeID;
	}
}