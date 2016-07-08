#include <InputWrapper.h>
#include <Game.h>
#include <Engine.h>
#include <DL_Debug.h>

int main()
{
	Easy3D::Engine::Create({ 1280.f, 720.f });

	Game game;

	bool isRunning = true;
	while (isRunning == true)
	{
		Easy3D::Engine::GetInstance()->Run();

		CU::InputWrapper::GetInstance()->Update();

		isRunning = game.Update();
		game.Render();
		Easy3D::Engine::GetInstance()->Render();
	}

	Easy3D::Engine::Destroy();

	DL_Debug::Debug::Destroy();
	return 0;
}