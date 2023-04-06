#pragma once 

#include <Moon/EntityComponent/Entity.h>
#include <EntityComponent/Components/SpriteRenderer.h>

class King : public Moon::Entity
{
public:
	King();

	virtual void Begin() override;
	virtual void Loop(float r_DeltaTime) override;
	virtual void Finish() override;

private:
	Moon::SpriteRenderer* m_Renderer;
};