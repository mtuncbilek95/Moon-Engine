#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/Assets/SpriteObject.h>

namespace Moon
{
	typedef std::unordered_map<int, SpriteObject*> SpriteHash;

	class AnimationClipObject
	{

	public:
		AnimationClipObject(int desiredSpeed) : m_DesiredSpeed(desiredSpeed)
		{
		}

		void AddSprite(int p_PlayStep, Sprite* r_Sprite)
		{
			m_Sprites.insert({ p_PlayStep, r_Sprite });
		}

		int GetDesiredSpeed()
		{
			return m_DesiredSpeed;
		}

	private:
		int m_DesiredSpeed;

	private:
		SpriteHash m_Sprites;
	};
}