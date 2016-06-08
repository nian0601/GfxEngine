#include "stdafx.h"

#include "AssetContainer.h"
#include "GBuffer.h"
#include "DeferredRenderer.h"
#include "Scene.h"
#include "Renderer.h"

namespace Easy3D
{
	DeferredRenderer::DeferredRenderer()
	{
		myGBuffer = new GBuffer();

		myFullscreenEffect = AssetContainer::GetInstance()->LoadEffect("Data/Shader/S_effect_fullscreen.fx");

		myCubemap = AssetContainer::GetInstance()->RequestTexture("Data/Texture/church_cubemap.dds");

		myRenderer = new Renderer(myFullscreenEffect);
		myRenderer->SetClearColor({ 0.4f, 0.4f, 0.4f, 1.f });
	}


	DeferredRenderer::~DeferredRenderer()
	{
		SAFE_DELETE(myGBuffer);
		SAFE_DELETE(myRenderer);
	}

	void DeferredRenderer::Render(Scene* aScene)
	{
		RenderToGBuffer(aScene);
		myRenderer->SetBackbufferAsTarget();
		myRenderer->ApplyRenderTargetAndDepthStencil();

		RenderAmbientPass();
	}

	void DeferredRenderer::Resize(float aWidth, float aHeight)
	{
		myGBuffer->Resize(aWidth, aHeight);
	}

	void DeferredRenderer::RenderToGBuffer(Scene* aScene)
	{
		myRenderer->ClearRenderTarget(myGBuffer->myAlbedoAndMetalness);
		myRenderer->ClearRenderTarget(myGBuffer->myNormalAndRoughness);
		myRenderer->ClearRenderTarget(myGBuffer->myDepth);
		myRenderer->ClearDepthStencil(myGBuffer->myDepthStencil);

		myRenderer->AddRenderTarget(myGBuffer->myAlbedoAndMetalness);
		myRenderer->AddRenderTarget(myGBuffer->myNormalAndRoughness);
		myRenderer->AddRenderTarget(myGBuffer->myDepth);
		myRenderer->SetDepthStencil(myGBuffer->myDepthStencil);
		myRenderer->ApplyRenderTargetAndDepthStencil();

		aScene->Render(myRenderer);
	}

	void DeferredRenderer::RenderAmbientPass()
	{
		myRenderer->SetEffect(myFullscreenEffect);
		myRenderer->SetTexture("AlbedoMetalnessTexture", myGBuffer->myAlbedoAndMetalness);
		myRenderer->SetTexture("NormalRoughnessTexture", myGBuffer->myNormalAndRoughness);
		myRenderer->SetTexture("DepthTexture", myGBuffer->myDepth);
		myRenderer->SetTexture("Cubemap", myCubemap);

		myRenderer->RenderFullScreen("Deferred_Ambient");
	}

}