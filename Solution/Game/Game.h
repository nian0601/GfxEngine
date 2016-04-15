#pragma once

namespace Frost
{
	class Camera;
	class Effect;
	class Instance;
}

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

private:
	Frost::Camera* myCamera;
	Frost::Instance* myInstance;
	Frost::Effect* myEffect;
};

