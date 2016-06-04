#include <Windows.h>
#include <InputWrapper.h>
#include <Game.h>
#include <Engine.h>
#include <DL_Debug.h>

Game* globalGame = nullptr;
int globalClientWidth = 800;
int globalClientHeight = 600;
bool globalIsResizing = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void OnResize();
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	DL_Debug::Debug::Create();

	HWND hwnd;
	Easy3D::Engine::Create();
	Easy3D::Engine::GetInstance()->CreateWindow(hwnd, WndProc, { 1280.f, 720.f }, "Test");
	Easy3D::Engine::GetInstance()->CreateDirectX(hwnd);

	globalGame = new Game();

	CU::InputWrapper::Create(hwnd, GetModuleHandle(NULL), DISCL_NONEXCLUSIVE
		| DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	MSG msg;
	bool isRunning = true;
	while (isRunning == true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			CU::InputWrapper::GetInstance()->Update();

			isRunning = globalGame->Update();
			globalGame->Render();
			Easy3D::Engine::GetInstance()->Render();
		}
	}

	delete globalGame;
	globalGame = nullptr;

	Easy3D::Engine::Destroy();

	DL_Debug::Debug::Destroy();
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:
		CU::InputWrapper::GetInstance()->ToggleWindowActive();
		break;
	case WM_SIZE:
	{
		globalClientWidth = LOWORD(lParam);
		globalClientHeight = HIWORD(lParam);

		if (LOWORD(wParam) == SIZE_MAXIMIZED)
		{
			OnResize();
		}
		else if (LOWORD(wParam) == SIZE_RESTORED)
		{
			if (globalIsResizing == false)
			{
				OnResize();
			}
		}
		break;
	}
	case WM_ENTERSIZEMOVE:
		if (globalGame != nullptr)
		{
			globalIsResizing = true;
		}
		break;
	case WM_EXITSIZEMOVE:
		if (globalGame != nullptr)
		{
			globalIsResizing = false;
			OnResize();
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void OnResize()
{
	//int* apa = nullptr;
	//*apa = 5;

	//Engine::GetInstance()->OnResize(globalClientWidth, globalClientHeight);

	if (globalGame != nullptr)
	{
		//globalGame->OnResize(globalClientWidth, globalClientHeight);
	}
}
