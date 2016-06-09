#pragma once
#include <CUMap.h>
#include <CUString.h>
#include "EngineTypes.h"
#include <GrowingArray.h>
#include <Vector.h>

namespace std
{
	class thread;
}

namespace Easy3D
{
	class Effect;
	class Instance;
	class IModelFactory;
	class ModelData;
	class Texture;

	class AssetContainer
	{
	public:
		static AssetContainer* GetInstance();
		static void Destroy();

		Instance* LoadModel(const CU::String<50>& aModelPath, const CU::String<50>& aEffectPath);
		ModelData* GetModel(ModelID aID);

		EffectID LoadEffect(const CU::String<50>& aFilePath);
		Effect* GetEffect(EffectID aID);

		Texture* RequestTexture(const CU::String<64>& aFilePath);

	private:
		AssetContainer();
		~AssetContainer();

		void Run();

		IModelFactory* myModelFactory;

		CU::Map<EffectID, Effect*> myEffects;
		CU::Map<CU::String<50>, EffectID> myEffectsID;
		EffectID myNextEffectID;

		CU::Map<ModelID, ModelData*> myModels;
		CU::Map<CU::String<50>, ModelID> myModelID;
		ModelID myNextModelID;

		CU::Map<CU::String<64>, Texture*> myTextures;

		static AssetContainer* myInstance;
	};
}