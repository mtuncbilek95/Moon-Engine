#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class Sprite;

	class AnimationClipObject
	{
		friend class SpriteAnimation;

	public:
		AnimationClipObject(int desiredSpeed) : m_AnimationName(clipName), m_DesiredSpeed(desiredSpeed)
		{

		}

	private:
		int m_DesiredSpeed;

		std::vector<Sprite*> m_Sprites;
	};
}