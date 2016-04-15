#include "Game.h"

#include <AssetSystem.h>
#include <Camera.h>
#include <ModelProxy.h>
#include <Instance.h>
#include <Effect.h>

Game::Game()
{
	myCamera = new Frost::Camera();

	myEffect = new Frost::Effect();
	myEffect->Init("Data/Shader/S_effect_cube3d.fx");

	myInstance = Frost::AssetSystem::GetInstance()->RequestCube({ 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f, 1.f }, *myEffect);
	myInstance->SetPosition({ 0.f, -1.f, 3.f });
}


Game::~Game()
{
}

void Game::Update()
{

}

void Game::Render()
{
	myInstance->Render(*myCamera);
}
