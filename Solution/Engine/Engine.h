#pragma once
#include <windef.h>
#include <string>
#include <WinUser.h>
#include <Vector.h>

#include "Model.h"
#include "Effect.h"

#undef CreateWindow


struct ID3D11Device;
struct ID3D11DeviceContext;

namespace Frost
{
	class DirectX;

	class Engine
	{
	public:
		static void Create();
		static void Destroy();
		static Engine* GetInstance();

		void CreateWindow(HWND& aHwnd, WNDPROC aWndProc, const CU::Vector2<float>& aSize, const std::string& aTitle);
		void CreateDirectX(const HWND& aHwnd);

		void Render();

		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetContext() const;

		void SetBackbufferAsRenderTarget();

		const CU::Vector2<float>& GetWindowSize() const;

	private:
		Engine();
		~Engine();

		DirectX* myDirectX;
		CU::Vector2<float> myWindowSize;

		static Engine* myInstance;
	};

	inline const CU::Vector2<float>& Engine::GetWindowSize() const
	{
		return myWindowSize;
	}
}