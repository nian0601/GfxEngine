#include "stdafx.h"

#include <AssetContainer.h>
#include <Camera.h>
#include <Effect.h>
#include "Game.h"
#include <Instance.h>
#include <ModelProxy.h>
#include <Scene.h>
#include <TimerManager.h>

Game::Game()
{
	myCamera = new Frost::Camera();

	myInstances.Init(16);

	myInstances.Add(Frost::AssetContainer::GetInstance()->RequestModel("Data/Model/PBL_Arm/pbl_metalness_arm_ascii.fbx", "Data/Shader/S_effect_pbl.fx"));
	myInstances.GetLast()->SetPosition({ -1.2f, -1.f, 5.f });

	myScene = new Frost::Scene();
	myScene->SetCamera(*myCamera);

	for each (Frost::Instance* instance in myInstances)
	{
		myScene->AddInstance(instance);
	}

	myTimerManager = new CU::TimerManager();
}


Game::~Game()
{
	myInstances.DeleteAll();
	SAFE_DELETE(myTimerManager);
}

void Game::Update()
{
	myTimerManager->Update();
	float delta = myTimerManager->GetMasterTimer().GetTime().GetFrameTime();
	myCamera->Update();
	UpdateCamera(delta);
}

void Game::Render()
{
	myScene->Render();
}

void Game::UpdateCamera(float aDelta)
{
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
