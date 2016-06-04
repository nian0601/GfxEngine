#pragma once

#include <CUMap.h>
#include <CUString.h>
#include "EngineTypes.h"

namespace Easy3D
{
	

	class Effect;
	class Texture;
	
	class GPUContainer
	{
	public:
		static GPUContainer* GetInstance();
		static void Destroy();

		EffectID LoadEffect(const CU::String<50>& aFilePath);
		Effect* GetEffect(EffectID aID);

		Texture* RequestTexture(const CU::String<50>& aFilePath);

	private:
		GPUContainer();
		~GPUContainer();
		
		CU::Map<EffectID, Effect*> myEffects;
		CU::Map<CU::String<50>, EffectID> myEffectsID;
		EffectID myNextEffectID;

		CU::Map<CU::String<50>, Texture*> myTextures;

		static GPUContainer* myInstance;
	};
}