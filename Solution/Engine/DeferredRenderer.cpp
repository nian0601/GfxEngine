#include "stdafx.h"

#include "AssetContainer.h"
#include <d3d11.h>
#include "GBuffer.h"
#include "Texture.h"
#include "DeferredRenderer.h"
#include "Scene.h"


namespace Easy3D
{
	DeferredRenderer::DeferredRenderer()
	{
		myGBuffer = new GBuffer();

		myFullscreenEffect = Easy3D::AssetContainer::GetInstance()->RequestEffect("Data/Shader/S_effect_fullscreen.fx");
		InitFullscreenQuad(myFullscreenEffect);

		myCubemap = AssetContainer::GetInstance()->RequestTexture("Data/Texture/church_cubemap.dds");
	}


	DeferredRenderer::~DeferredRenderer()
	{
		SAFE_DELETE(myGBuffer);
	}

	void DeferredRenderer::Render(Scene* aScene)
	{
		RenderToGBuffer(aScene);
		Engine::GetInstance()->SetBackbufferAsRenderTarget();

		ActiveFullscreenQuad();
		RenderAmbientPass();
	}

	void DeferredRenderer::Resize(float aWidth, float aHeight)
	{
		myGBuffer->Resize(aWidth, aHeight);
	}

	void DeferredRenderer::RenderToGBuffer(Scene* aScene)
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

	void DeferredRenderer::RenderAmbientPass()
	{
		myGBuffer->Set(myFullscreenEffect);
		myFullscreenEffect->SetCubemap(myCubemap->GetShaderView());

		RenderFullscreenQuad(myFullscreenEffect, "Deferred_Ambient");

		myFullscreenEffect->SetCubemap(nullptr);
		myGBuffer->UnSet(myFullscreenEffect);
	}

}