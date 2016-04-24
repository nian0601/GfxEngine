#pragma once

#include <GrowingArray.h>

namespace Frost
{
	class Camera;
	class Instance;
	class Renderer;
	class Scene;
}

namespace CU
{
	class TimerManager;
}

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

private:
	void UpdateCamera(float aDelta);

	Frost::Camera* myCamera;
	Frost::Scene* myScene;
	Frost::Renderer* myRenderer;

	CU::GrowingArray<Frost::Instance*> myInstances;

	CU::TimerManager* myTimerManager;

	float myMetalness;
	float myRoughness;
};

