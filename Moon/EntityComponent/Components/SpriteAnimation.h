#pragma once

#include <Core/MoonCore.h>

#include <EntityComponent/EntityCore.h>
#include <EntityComponent/Component.h>

class SpriteRenderer;

class SpriteAnimation : public Component
{
public:
	SpriteAnimation() : Component() {}
	~SpriteAnimation() {}

	virtual bool Initialize() override
	{
		return GetEntity()->HasComponent<SpriteRenderer>();
	}

	virtual void UpdateMatrix() override {}

	void AddClip(AnimationClip* clip)
	{

		m_AnimClips[clip->GetName()] = clip;
	}

	void RemoveClip(string clipName)
	{
		m_AnimClips.erase(clipName);
	}

	void Play(string clipName)
	{

	}

private:
	std::unordered_map<string, AnimationClip*> m_AnimClips;
};