#pragma once
#include "FullscreenQuad.h"

namespace Easy3D
{
	class Effect;
	class GBuffer;
	class Scene;
	class Texture;

	class Renderer : public FullscreenQuad
	{
	public:
		Renderer();
		~Renderer();

		void Render(Scene* aScene);

		void Resize(float aWidth, float aHeight);

	private:
		void RenderToGBuffer(Scene* aScene);
		void RenderAmbientPass();

		Effect* myFullscreenEffect;
		GBuffer* myGBuffer;
		Texture* myCubemap;
	};
}