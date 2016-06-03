#include "stdafx.h"

#include "AssetContainer.h"
#include <d3d11.h>
#include "GBuffer.h"
#include "Texture.h"
#include "Renderer.h"
#include "Scene.h"


namespace Easy3D
{
	Renderer::Renderer()
	{
		myGBuffer = new GBuffer();

		myFullscreenEffect = Easy3D::AssetContainer::GetInstance()->RequestEffect("Data/Shader/S_effect_fullscreen.fx");
		InitFullscreenQuad(myFullscreenEffect);

		myCubemap = AssetContainer::GetInstance()->RequestTexture("Data/Texture/church_cubemap.dds");
	}


	Renderer::~Renderer()
	{
		SAFE_DELETE(myGBuffer);
	}

	void Renderer::Render(Scene* aScene)
	{
		RenderToGBuffer(aScene);
		Engine::GetInstance()->SetBackbufferAsRenderTarget();

		ActiveFullscreenQuad();
		RenderAmbientPass();
	}

	void Renderer::Resize(float aWidth, float aHeight)
	{
		myGBuffer->Resize(aWidth, aHeight);
	}

	void Renderer::RenderToGBuffer(Scene* aScene)
	{
		myGBuffer->Clear({ 0.4f, 0.4f, 0.4f, 1.f });

		ID3D11RenderTargetView* renderTargets[3];
		renderTargets[0] = myGBuffer->myAlbedoAndMetalness->GetRenderTarget();
		renderTargets[1] = myGBuffer->myNormalAndRoughness->GetRenderTarget();
		renderTargets[2] = myGBuffer->myDepth->GetRenderTarget();

		ID3D11DepthStencilView* depth = myGBuffer->myDepthStencil->GetDepthStencil();

		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();

		context->OMSetRenderTargets(3, renderTargets, depth);

		aScene->Render();
	}

	void Renderer::RenderAmbientPass()
	{
		myGBuffer->Set(myFullscreenEffect);
		myFullscreenEffect->SetCubemap(myCubemap->GetShaderView());

		RenderFullscreenQuad(myFullscreenEffect, "Deferred_Ambient");

		myFullscreenEffect->SetCubemap(nullptr);
		myGBuffer->UnSet(myFullscreenEffect);
	}

}