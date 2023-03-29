#pragma once

#include <Moon/Core/MoonCore.h>

#include <Moon/Graphics/RenderCore.h>

namespace Moon
{
	struct AtlasConstantBuffer
	{
		XMINT2 AtlasPoint;
	};

	struct ModelMatrix
	{
		XMMATRIX WorldMatrix;
		XMMATRIX ViewMatrix;
		XMMATRIX ProjectionMatrix;
	};
}