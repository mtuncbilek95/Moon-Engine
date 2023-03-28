#pragma once

#include <Moon/Core/MoonCore.h>

#include <Moon/EntityComponent/EntityCore.h>
#include <Moon/EntityComponent/Component.h>

#include <Moon/Assets/AnimationClipObject.h>

namespace Moon
{
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

		virtual void Update() override {}

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
			auto& element = m_AnimClips.find(clipName);
			AnimationClipObject* clip = element.second;

			for (auto& el : clip->m_Sprites)
			{

			}

		}

	private:
		std::unordered_map<string, AnimationClipObject*> m_AnimClips;
	};
}