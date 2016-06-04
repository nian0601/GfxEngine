#pragma once
#include "BaseModel.h"

namespace Easy3D
{
	class Effect;

	class FullscreenQuad : public BaseModel
	{
	public:
		FullscreenQuad();
		~FullscreenQuad();

		void InitFullscreenQuad(Effect* aEffect);
		void ActivateFullscreenQuad();
		void RenderFullscreenQuad(Effect* aEffect, const CU::String<30>& aTechnique);
	protected:
	};
}