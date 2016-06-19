#pragma once

#include <GrowingArray.h>
#include <World.h>

namespace Easy3D
{
	class Camera;
	class Instance;
	class DeferredRenderer;
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

	bool Update();
	void Render();

private:
	void UpdateCamera(float aDelta);
	void LoadLevel();

	Easy3D::Camera* myCamera;
	Easy3D::Scene* myScene;
	Easy3D::DeferredRenderer* myRenderer;

	CU::TimerManager* myTimerManager;

	World myWorld;
};

