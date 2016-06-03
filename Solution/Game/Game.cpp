#include "stdafx.h"

#include <AssetContainer.h>
#include <Camera.h>
#include <Effect.h>
#include "Game.h"
#include <Instance.h>
#include <ModelProxy.h>
#include <Scene.h>
#include <TimerManager.h>

#include <FullscreenQuad.h>
#include <DeferredRenderer.h>

Game::Game()
{
	myCamera = new Easy3D::Camera();

	myInstances.Init(16);

	myInstances.Add(Easy3D::AssetContainer::GetInstance()->RequestModel("Data/Model/PBL_Arm/pbl_metalness_arm_ascii.fbx", "Data/Shader/S_effect_model.fx"));
	//myInstances.Add(Frost::AssetContainer::GetInstance()->RequestModel("Data/Model/Sphere/Sphere.fbx", "Data/Shader/S_effect_pbl_no_textures.fx"));
	myInstances.GetLast()->SetPosition({ -1.2f, -1.f, 5.f });

	myScene = new Easy3D::Scene();
	myScene->SetCamera(*myCamera);

	for each (Easy3D::Instance* instance in myInstances)
	{
		myScene->AddInstance(instance);
	}

	myTimerManager = new CU::TimerManager();

	myMetalness = 0.f;
	myRoughness = 0.f;

	myRenderer = new Easy3D::DeferredRenderer();
}


Game::~Game()
{
	myInstances.DeleteAll();
	SAFE_DELETE(myTimerManager);
	SAFE_DELETE(myRenderer);
}

void Game::Update()
{
	myTimerManager->Update();
	float delta = myTimerManager->GetMasterTimer().GetTime().GetFrameTime();
	myCamera->Update();
	UpdateCamera(delta);

	CU::InputWrapper* input = CU::InputWrapper::GetInstance();

	if (input->KeyIsPressed(DIK_1))
	{
		myMetalness -= 0.4f * delta;
	}
	if (input->KeyIsPressed(DIK_2))
	{
		myMetalness += 0.4f * delta;
	}
	if (input->KeyIsPressed(DIK_3))
	{
		myRoughness -= 0.4f * delta;
	}
	if (input->KeyIsPressed(DIK_4))
	{
		myRoughness += 0.4f * delta;
	}

	myMetalness = max(myMetalness, 0.f);
	myMetalness = min(1.f, myMetalness);
	myRoughness = max(myRoughness, 0.f);
	myRoughness = min(1.f, myRoughness);

	//Frost::EffectContainer::GetInstance()->Get("Data/Shader/S_effect_pbl_no_textures.fx")->SetMetalness(myMetalness);
	//Frost::EffectContainer::GetInstance()->Get("Data/Shader/S_effect_pbl_no_textures.fx")->SetRoughness(myRoughness);
	Easy3D::AssetContainer::GetInstance()->RequestEffect("Data/Shader/S_effect_model.fx")->SetMetalness(myMetalness);
	Easy3D::AssetContainer::GetInstance()->RequestEffect("Data/Shader/S_effect_model.fx")->SetRoughness(myRoughness);
}

void Game::Render()
{
	myRenderer->Render(myScene);
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
