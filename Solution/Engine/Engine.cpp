#include "stdafx.h"

#include "AssetContainer.h"
#include "Engine.h"
#include "GPUContext.h"
#include "IGame.h"
#include <InputWrapper.h>
#include <TimerManager.h>
#include "WindowHandler.h"

namespace Easy3D
{
	Engine* Engine::myInstance = nullptr;

	void Engine::Create(const CU::Vector2<float>& aSize, IGame& aGame)
	{
		DL_ASSERT_EXP(myInstance == nullptr, "Cant create Engine multiple times");
		myInstance = new Engine(aSize, aGame);
	}

	void Engine::Destroy()
	{
		SAFE_DELETE(myInstance);
	}

	Engine* Engine::GetInstance()
	{
		return myInstance;
	}

	void Engine::Run()
	{
		myIsRunning = true;
		while (myIsRunning == true)
		{
			if (myWindowHandler->PumpEvent() == false)
			{
				myIsRunning = false;
			}
			else
			{
				if (myWindowHandler->GetShouldResize() == true)
				{
					myWindowHandler->HasResized();
					myGame->OnResize(myWindowHandler->GetNewSize().x, myWindowHandler->GetNewSize().y);
				}

				myTimerManager->Update();
				CU::InputWrapper::GetInstance()->Update();

				myIsRunning = myGame->Update(myTimerManager->GetMasterTimer().GetTime().GetFrameTime());

				myGPUContext->FinishFrame();

				myTimerManager->CapFrameRate(60.f);
			}
		}
	}

	void Engine::Init()
	{
		myGame->Init(*this);
	}

	Engine::Engine(const CU::Vector2<float>& aSize, IGame& aGame)
		: myGPUContext(nullptr)
		, myWindowSize(aSize)
		, myGame(&aGame)
	{
		myWindowHandler = new WindowHandler(myWindowSize);
		myGPUContext = new GPUContext(myWindowSize, myWindowHandler->GetHwnd());
		myAssetContainer = new AssetContainer(*myGPUContext);
		myTimerManager = new CU::TimerManager();

		CU::InputWrapper::Create(myWindowHandler->GetHwnd(), GetModuleHandle(NULL), DISCL_NONEXCLUSIVE
			| DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}


	Engine::~Engine()
	{
		SAFE_DELETE(myWindowHandler);
		SAFE_DELETE(myGPUContext);
		SAFE_DELETE(myAssetContainer);
		SAFE_DELETE(myTimerManager)
		DL_Debug::Debug::Destroy();
		CU::InputWrapper::Destroy();
	}

	void Engine::Render()
	{
		myGPUContext->FinishFrame();
	}
}