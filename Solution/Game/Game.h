#pragma once

#include <GrowingArray.h>

namespace Easy3D
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

	Easy3D::Camera* myCamera;
	Easy3D::Scene* myScene;
	Easy3D::Renderer* myRenderer;

	CU::GrowingArray<Easy3D::Instance*> myInstances;

	CU::TimerManager* myTimerManager;

	float myMetalness;
	float myRoughness;
};

