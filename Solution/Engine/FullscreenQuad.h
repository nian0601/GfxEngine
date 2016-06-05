#pragma once
#include "BaseModel.h"
#include "EngineTypes.h"

namespace Easy3D
{
	class Effect;

	class FullscreenQuad : public BaseModel
	{
	public:
		FullscreenQuad();
		~FullscreenQuad();

		void InitFullscreenQuad(EffectID aEffect);
		void ActivateFullscreenQuad();
		void RenderFullscreenQuad(EffectID aEffect, const CU::String<30>& aTechnique);
	};
}