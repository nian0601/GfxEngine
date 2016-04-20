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
	class Texture;

	class AssetContainer
	{
	public:
		static AssetContainer* GetInstance();
		static void Destroy();


		Instance* RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, const std::string& aEffectPath);
		Instance* RequestModel(const std::string& aModelPath, const std::string& aEffectPath);

		Effect* RequestEffect(const std::string& aFilePath);
		Texture* RequestTexture(const std::string& aFilePath);

	private:
		AssetContainer();
		~AssetContainer();

		void Run();

		CU::GrowingArray<Model*> myNonDGFXModels;
		IModelFactory* myModelFactory;

		std::unordered_map<std::string, Effect*> myEffects;
		std::unordered_map<std::string, Texture*> myTextures;

		static AssetContainer* myInstance;
	};
}