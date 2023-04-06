#include "King.h"

#include <Log/Log.h>

King::King() : Entity()
{
	m_Renderer = AddComponent<Moon::SpriteRenderer>();
}


void King::Begin()
{
	Moon::Log::ConsoleLog(Moon::LogType::Info, "King has been initialized.");
}

void King::Loop(float r_DeltaTime)
{
}

void King::Finish()
{
}
