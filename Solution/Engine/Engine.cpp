#include "stdafx.h"
#include "Engine.h"
#include "GPUContext.h"
#include <InputWrapper.h>
#include "WindowHandler.h"

namespace Easy3D
{
	Engine* Engine::myInstance = nullptr;

	void Engine::Create(const CU::Vector2<float>& aSize)
	{
		DL_ASSERT_EXP(myInstance == nullptr, "Cant create Engine multiple times");
		myInstance = new Engine(aSize);
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
		//while (myIsRunning == true)
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
				}
			}
		}
	}

	Engine::Engine(const CU::Vector2<float>& aSize)
		: myGPUContext(nullptr)
		, myWindowSize(aSize)
	{
		myWindowHandler = new WindowHandler(myWindowSize);
		myGPUContext = new GPUContext(myWindowSize, myWindowHandler->GetHwnd());

		CU::InputWrapper::Create(myWindowHandler->GetHwnd(), GetModuleHandle(NULL), DISCL_NONEXCLUSIVE
			| DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}


	Engine::~Engine()
	{
		SAFE_DELETE(myGPUContext);
	}

	void Engine::Render()
	{
		myGPUContext->FinishFrame();
	}
}