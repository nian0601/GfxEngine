#pragma once

#include <CUString.h>
#include <Vector.h>
#include <windef.h>
#include <WinUser.h>

#undef CreateWindow

struct ID3D11Device;
struct ID3D11DeviceContext;


namespace Easy3D
{
	struct Backbuffer;

	class DirectX;
	class GPUContext;

	class Engine
	{
	public:
		static void Create();
		static void Destroy();
		static Engine* GetInstance();

		void CreateWindow(HWND& aHwnd, WNDPROC aWndProc, const CU::Vector2<float>& aSize, const CU::String<30>& aTitle);
		void CreateDirectX(const HWND& aHwnd);

		void Render();

		GPUContext& GetGPUContext();
		const CU::Vector2<float>& GetWindowSize() const;

	private:
		Engine();
		~Engine();

		GPUContext* myGPUContext;
		CU::Vector2<float> myWindowSize;

		static Engine* myInstance;
	};

	inline GPUContext& Engine::GetGPUContext()
	{
		return *myGPUContext;
	}

	inline const CU::Vector2<float>& Engine::GetWindowSize() const
	{
		return myWindowSize;
	}
}