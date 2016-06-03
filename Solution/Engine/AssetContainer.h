#pragma once
#include <CUString.h>
#include <GrowingArray.h>
#include <Vector.h>

namespace std
{
	class thread;
}

namespace Easy3D
{
	class Instance;
	class Effect;
	class Model;
	class IModelFactory;
	class Texture;

	class AssetContainer
	{
	public:
		static AssetContainer* GetInstance();
		static void Destroy();


		Instance* RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, const CU::String<50>& aEffectPath);
		Instance* RequestModel(const CU::String<50>& aModelPath, const CU::String<50>& aEffectPath);

		

	private:
		AssetContainer();
		~AssetContainer();

		void Run();

		CU::GrowingArray<Model*> myNonDGFXModels;
		IModelFactory* myModelFactory;

		static AssetContainer* myInstance;
	};
}