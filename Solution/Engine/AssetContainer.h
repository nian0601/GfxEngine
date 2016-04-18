#pragma once
#include <GrowingArray.h>
#include <Vector.h>

namespace std
{
	class thread;
}

namespace Frost
{
	class Instance;
	class Effect;
	class Model;
	class IModelFactory;

	class AssetContainer
	{
	public:
		static AssetContainer* GetInstance();
		static void Destroy();


		Instance* RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, const std::string& aEffectPath);
		Instance* RequestModel(const std::string& aModelPath, const std::string& aEffectPath);

	private:
		AssetContainer();
		~AssetContainer();

		void Run();

		CU::GrowingArray<Model*> myNonDGFXModels;
		IModelFactory* myModelFactory;

		static AssetContainer* myInstance;
	};
}