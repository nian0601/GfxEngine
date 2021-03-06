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

#include <XMLReader.h>
#include <MathHelper.h>

Game::Game()
{
	myCamera = new Easy3D::Camera();

	myInstances.Init(16);

	XMLReader reader;
	reader.OpenDocument("Data/Resource/Level/Level_01.xml");
	for (tinyxml2::XMLElement* cube = reader.ForceFindFirstChild("Cube"); cube != nullptr; cube = reader.FindNextElement(cube, "Cube"))
	{
		CU::Vector3<float> position;
		CU::Vector3<float> rotation;
		CU::Vector3<float> scale;

		reader.ForceReadAttribute(reader.ForceFindFirstChild(cube, "Position"), "x", "y", "z", position);
		reader.ForceReadAttribute(reader.ForceFindFirstChild(cube, "Scale"), "x", "y", "z", scale);
		reader.ForceReadAttribute(reader.ForceFindFirstChild(cube, "Rotation"), "x", "y", "z", rotation);

		rotation.x = CU::Math::DegreeToRad(rotation.x);
		rotation.y = CU::Math::DegreeToRad(rotation.y);
		rotation.z = CU::Math::DegreeToRad(rotation.z);

		myInstances.Add(Easy3D::AssetContainer::GetInstance()->LoadModel("Data/Resource/Model/Cube/SM_1x1_cube.fbx", "Data/Resource/Shader/S_effect_cube.fx"));
		myInstances.GetLast()->SetPosition(position);
		myInstances.GetLast()->SetRotation(rotation);
		myInstances.GetLast()->SetScale(scale);

	}
	reader.CloseDocument();

	myScene = new Easy3D::Scene();
	myScene->SetCamera(*myCamera);

	for each (Easy3D::Instance* instance in myInstances)
	{
		myScene->AddInstance(instance);
	}

	myScene->AddLight(new Easy3D::PointLight({ -1.2f, -1.f, 3.f }, { 1.f, 0.f, 0.f, 3.f }, 4.f));

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
