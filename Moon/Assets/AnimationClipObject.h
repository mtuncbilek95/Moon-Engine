#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class SpriteObject;

	class AnimationClipObject
	{
		friend class SpriteAnimation;

	public:
		AnimationClipObject(int desiredSpeed) : m_AnimationName(clipName), m_DesiredSpeed(desiredSpeed)
		{
		}

	private:
		int m_DesiredSpeed;

		std::vector<SpriteObject*> m_Sprites;
	};
}