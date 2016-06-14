#include "stdafx.h"

#include <AssetContainer.h>
#include <Camera.h>
#include <Effect.h>
#include "Game.h"
#include <Instance.h>
#include <Scene.h>
#include <TimerManager.h>
#include <DeferredRenderer.h>
#include <PointLight.h>

Game::Game()
{
	myCamera = new Easy3D::Camera();

	myInstances.Init(16);

	//myInstances.Add(Easy3D::AssetContainer::GetInstance()->LoadModel("Data/Resource/Model/PBL_test_balls.fbx", "Data/Resource/Shader/S_effect_model.fx"));
	myInstances.Add(Easy3D::AssetContainer::GetInstance()->LoadModel("Data/Resource/Model/PBL_Arm/pbl_metalness_arm_binary.fbx", "Data/Resource/Shader/S_effect_model.fx"));

	myInstances.GetLast()->SetPosition({ -1.2f, -1.f, 5.f });

	myScene = new Easy3D::Scene();
	myScene->SetCamera(*myCamera);

	for each (Easy3D::Instance* instance in myInstances)
	{
		myScene->AddInstance(instance);
	}

	myScene->AddLight(new Easy3D::PointLight({ -1.2f, -1.f, 5.f }, { 1.f, 0.f, 0.f, 3.f }, 4.f));

	myTimerManager = new CU::TimerManager();
	myRenderer = new Easy3D::DeferredRenderer();
}


Game::~Game()
{
	myInstances.DeleteAll();
	SAFE_DELETE(myTimerManager);
	SAFE_DELETE(myRenderer);

	Easy3D::AssetContainer::Destroy();
}

bool Game::Update()
{
	myTimerManager->Update();
	float delta = myTimerManager->GetMasterTimer().GetTime().GetFrameTime();
	
	UpdateCamera(delta);

	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_ESCAPE))
	{
		return false;
	}

	return true;
}

void Game::Render()
{
	myRenderer->Render(myScene);
}

void Game::UpdateCamera(float aDelta)
{
	myCamera->Update();

	float speed = 10.f * aDelta;
	CU::InputWrapper* input = CU::InputWrapper::GetInstance();
	CU::Vector3<float> dir;

	if (input->KeyIsPressed(DIK_W))
	{
		dir.z = 1.f;
	}
	else if (input->KeyIsPressed(DIK_S))
	{
		dir.z = -1.f;
	}

	if (input->KeyIsPressed(DIK_A))
	{
		dir.x = -1.f;
	}
	else if (input->KeyIsPressed(DIK_D))
	{
		dir.x = 1.f;
	}

	if (input->KeyIsPressed(DIK_Q))
	{
		dir.y = 1.f;
	}
	else if (input->KeyIsPressed(DIK_E))
	{
		dir.y = -1.f;
	}

	CU::Normalize(dir);
	myCamera->Move(dir * speed);

	if (input->KeyIsPressed(DIK_UP))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundX(-PI * 0.5f * aDelta));
	}
	else if (input->KeyIsPressed(DIK_DOWN))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundX(PI * 0.5f * aDelta));
	}
	else if (input->KeyIsPressed(DIK_LEFT))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundY(-PI * 0.5f * aDelta));
	}
	else if (input->KeyIsPressed(DIK_RIGHT))
	{
		myCamera->Rotate(CU::Matrix44<float>::CreateRotateAroundY(PI * 0.5f * aDelta));
	}
}
