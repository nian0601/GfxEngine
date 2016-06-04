#include "stdafx.h"

#include <d3d11.h>
#include "GBuffer.h"
#include "GPUContainer.h"
#include "Texture.h"
#include "DeferredRenderer.h"
#include "Scene.h"
#include "Renderer.h"

namespace Easy3D
{
	DeferredRenderer::DeferredRenderer()
	{
		myGBuffer = new GBuffer();

		myFullscreenEffect = GPUContainer::GetInstance()->LoadEffect("Data/Shader/S_effect_fullscreen.fx");

		myCubemap = GPUContainer::GetInstance()->RequestTexture("Data/Texture/church_cubemap.dds");

		myRenderer = new Renderer(myFullscreenEffect);
	}


	DeferredRenderer::~DeferredRenderer()
	{
		SAFE_DELETE(myGBuffer);
		SAFE_DELETE(myRenderer);
	}

	void DeferredRenderer::Render(Scene* aScene)
	{
		RenderToGBuffer(aScene);
		Engine::GetInstance()->SetBackbufferAsRenderTarget();

		RenderAmbientPass();
	}

	void DeferredRenderer::Resize(float aWidth, float aHeight)
	{
		myGBuffer->Resize(aWidth, aHeight);
	}

	void DeferredRenderer::RenderToGBuffer(Scene* aScene)
	{
		myRenderer->ClearRenderTarget(myGBuffer->myAlbedoAndMetalness, { 0.4f, 0.4f, 0.4f, 1.f });
		myRenderer->ClearRenderTarget(myGBuffer->myNormalAndRoughness, { 0.4f, 0.4f, 0.4f, 1.f });
		myRenderer->ClearRenderTarget(myGBuffer->myDepth, { 0.4f, 0.4f, 0.4f, 1.f });
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