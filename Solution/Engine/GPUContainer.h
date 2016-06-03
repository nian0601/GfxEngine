#pragma once

#include <CUMap.h>
#include <CUString.h>

namespace Easy3D
{
	class Effect;
	class Texture;
	
	class GPUContainer
	{
	public:
		static GPUContainer* GetInstance();
		static void Destroy();

		Effect* RequestEffect(const CU::String<50>& aFilePath);
		Texture* RequestTexture(const CU::String<50>& aFilePath);

	private:
		GPUContainer();
		~GPUContainer();
		
		CU::Map<CU::String<50>, Effect*> myEffects;
		CU::Map<CU::String<50>, Texture*> myTextures;

		static GPUContainer* myInstance;
	};
}