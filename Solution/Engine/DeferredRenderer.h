#pragma once
#include "FullscreenQuad.h"

namespace Easy3D
{
	class Effect;
	class GBuffer;
	class Instance;
	class Scene;
	class Texture;
	class Renderer;

	class DeferredRenderer
	{
	public:
		DeferredRenderer();
		~DeferredRenderer();

		void Render(Scene* aScene);

		void Resize(float aWidth, float aHeight);

	private:
		void RenderToGBuffer(Scene* aScene);
		void RenderAmbientPass();
		void RenderPointLights(Scene* aScene);

		EffectID myFullscreenEffect;
		EffectID myPointLightEffect;
		GBuffer* myGBuffer;
		Texture* myCubemap;

		Renderer* myRenderer;
		Instance* myPointLightInstance;
	};
}