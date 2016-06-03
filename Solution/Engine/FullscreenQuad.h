#pragma once
#include "BaseModel.h"
#include <string>

namespace Easy3D
{
	class Effect;

	class FullscreenQuad : public BaseModel
	{
	public:
		FullscreenQuad();
		~FullscreenQuad();

		void InitFullscreenQuad(Effect* aEffect);
		void ActiveFullscreenQuad();
		void RenderFullscreenQuad(Effect* aEffect, const CU::String<30>& aTechnique);
	protected:
	};
}