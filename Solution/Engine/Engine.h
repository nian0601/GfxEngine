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
	class WindowHandler;

	class Engine
	{
	public:
		static void Create(const CU::Vector2<float>& aSize);
		static void Destroy();
		static Engine* GetInstance();

		void Run();

		void Render();

		GPUContext& GetGPUContext();
		const CU::Vector2<float>& GetWindowSize() const;

	private:
		Engine(const CU::Vector2<float>& aSize);
		~Engine();

		GPUContext* myGPUContext;
		WindowHandler* myWindowHandler;
		CU::Vector2<float> myWindowSize;
		bool myIsRunning;

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