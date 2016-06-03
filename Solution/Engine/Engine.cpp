#include "stdafx.h"
#include "Engine.h"
#include "DirectX.h"

namespace Easy3D
{
	Engine* Engine::myInstance = nullptr;

	void Engine::Create()
	{
		DL_ASSERT_EXP(myInstance == nullptr, "Cant create Engine multiple times");
		myInstance = new Engine();
	}

	void Engine::Destroy()
	{
		SAFE_DELETE(myInstance);
	}

	Engine* Engine::GetInstance()
	{
		return myInstance;
	}

	Engine::Engine()
		: myDirectX(nullptr)
	{
	}


	Engine::~Engine()
	{
		SAFE_DELETE(myDirectX);
	}

	void Engine::CreateWindow(HWND& aHwnd, WNDPROC aWndProc, const CU::Vector2<float>& aSize, const CU::String<30>& aTitle)
	{
		myWindowSize = aSize;

		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = aWndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = GetModuleHandle(NULL);
		wcex.hIcon = LoadIcon(wcex.hInstance, NULL);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = aTitle.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);

		DL_ASSERT_EXP(RegisterClassEx(&wcex) != FALSE, "Failed to RegisterClassEx");

		RECT rc = { 0, 0, int(aSize.x), int(aSize.y) };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		aHwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			aTitle.c_str(),
			aTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			rc.right - rc.left,
			rc.bottom - rc.top,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL);

		DL_ASSERT_EXP(aHwnd != nullptr, "Failed to CreateWindowEx");

		ShowWindow(aHwnd, 10);
		UpdateWindow(aHwnd);
	}

	void Engine::CreateDirectX(const HWND& aHwnd)
	{
		myDirectX = new DirectX();
		myDirectX->Init(aHwnd, myWindowSize);
	}

	void Engine::Render()
	{
		myDirectX->FinishFrame();
	}

	ID3D11Device* Engine::GetDevice() const
	{
		return myDirectX->GetDevice();
	}

	ID3D11DeviceContext* Engine::GetContext() const
	{
		return myDirectX->GetContext();
	}

	void Engine::SetBackbufferAsRenderTarget()
	{
		myDirectX->SetBackbufferAsRenderTarget();
	}

}