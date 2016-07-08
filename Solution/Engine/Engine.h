#pragma once

#include <CUString.h>
#include <Vector.h>
#include <windef.h>
#include <WinUser.h>

#undef CreateWindow

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace CU
{
	class TimerManager;
}

namespace Easy3D
{
	struct Backbuffer;

	class AssetContainer;
	class DirectX;
	class GPUContext;
	class WindowHandler;
	class IGame;

	class Engine
	{
	public:
		static void Create(const CU::Vector2<float>& aSize, IGame& aGame);
		static void Destroy();
		static Engine* GetInstance();

		void Run();
		void Init();

		void Render();

		GPUContext& GetGPUContext();
		AssetContainer& GetAssetContainer();
		const CU::Vector2<float>& GetWindowSize() const;

	private:
		Engine(const CU::Vector2<float>& aSize, IGame& aGame);
		~Engine();

		GPUContext* myGPUContext;
		WindowHandler* myWindowHandler;
		AssetContainer* myAssetContainer;
		IGame* myGame;
		CU::TimerManager* myTimerManager;

		CU::Vector2<float> myWindowSize;
		bool myIsRunning;

		static Engine* myInstance;
	};

	inline GPUContext& Engine::GetGPUContext()
	{
		return *myGPUContext;
	}

	inline AssetContainer& Engine::GetAssetContainer()
	{
		return *myAssetContainer;
	}

	inline const CU::Vector2<float>& Engine::GetWindowSize() const
	{
		return myWindowSize;
	}
}