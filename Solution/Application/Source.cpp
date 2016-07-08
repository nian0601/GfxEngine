#include <InputWrapper.h>
#include <Game.h>
#include <Engine.h>
#include <DL_Debug.h>

int main()
{
	Game game;
	Easy3D::Engine::Create({ 1280.f, 720.f }, game);

	Easy3D::Engine::GetInstance()->Init();

	Easy3D::Engine::GetInstance()->Run();

	Easy3D::Engine::Destroy();
	return 0;
}