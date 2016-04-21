#pragma once
#include "BaseModel.h"

namespace Frost
{
	class Effect;

	class FullscreenQuad : public BaseModel
	{
	public:
		FullscreenQuad();
		~FullscreenQuad();

		void InitFullscreenQuad(Effect* aEffect);
		void ActiveFullscreenQuad();
		void RenderFullscreenQuad(Effect* aEffect, const std::string& aTechnique);
	protected:
	};
}