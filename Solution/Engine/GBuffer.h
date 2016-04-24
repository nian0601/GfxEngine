#pragma once

#include <Vector.h>

namespace Frost
{
	class Effect;
	class Texture;

	class GBuffer
	{
	public:
		GBuffer();
		~GBuffer();

		void Set(Effect* aEffect);
		void UnSet(Effect* aEffect);
		void Clear(const CU::Vector4<float>& aColor);

		void Resize(float aWidth, float aHeight);

		Texture* myAlbedoAndMetalness;
		Texture* myNormalAndRoughness;
		Texture* myDepth;

		Texture* myDepthStencil;
	};
}