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
	class Texture;

	class AssetContainer
	{
	public:
		static AssetContainer* GetInstance();
		static void Destroy();

		Instance* RequestModel(const CU::String<50>& aModelPath, const CU::String<50>& aEffectPath);

		EffectID LoadEffect(const CU::String<50>& aFilePath);
		Effect* GetEffect(EffectID aID);

		Texture* RequestTexture(const CU::String<50>& aFilePath);

	private:
		AssetContainer();
		~AssetContainer();

		void Run();

		IModelFactory* myModelFactory;

		CU::Map<EffectID, Effect*> myEffects;
		CU::Map<CU::String<50>, EffectID> myEffectsID;
		EffectID myNextEffectID;

		CU::Map<CU::String<50>, Texture*> myTextures;

		static AssetContainer* myInstance;
	};
}