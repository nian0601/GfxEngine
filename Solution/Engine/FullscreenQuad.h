#pragma once
#include "EngineTypes.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include "GPUData.h"

namespace Easy3D
{
	class Effect;

	class FullscreenQuad
	{
	public:
		FullscreenQuad();
		~FullscreenQuad();

		void InitFullscreenQuad(EffectID aEffect);
		void ActivateFullscreenQuad();
		void RenderFullscreenQuad(EffectID aEffect, const CU::String<30>& aTechnique);

	private:
		GPUData myGPUData;
		
	};
}