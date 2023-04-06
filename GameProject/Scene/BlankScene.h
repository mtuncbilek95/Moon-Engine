#pragma once

#include <Moon/World/SceneObject.h>

class BlankScene : public Moon::SceneObject
{
public:
	BlankScene();

	virtual void Begin() override;
	virtual void Loop(float r_DeltaTime) override;
	virtual void Finish() override;
};