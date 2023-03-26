#pragma once

#include <Core/MoonCore.h>

class Sprite;

class AnimationClip
{
public:
	AnimationClip(string clipName, int desiredSpeed) : m_AnimationName(clipName), m_DesiredSpeed(desiredSpeed)
	{

	}
private:

	int m_DesiredSpeed;
};