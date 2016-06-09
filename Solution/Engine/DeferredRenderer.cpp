#include "stdafx.h"

#include "AssetContainer.h"
#include "GBuffer.h"
#include "DeferredRenderer.h"
#include "Instance.h"
#include "Scene.h"
#include "Renderer.h"
#include "PointLight.h"

namespace Easy3D
{
	DeferredRenderer::DeferredRenderer()
	{
		myGBuffer = new GBuffer();

		myFullscreenEffect = AssetContainer::GetInstance()->LoadEffect("Data/Resource/Shader/S_effect_fullscreen.fx");
		myPointLightEffect = AssetContainer::GetInstance()->LoadEffect("Data/Resource/Shader/S_effect_deferred_pointlight.fx");

		myCubemap = AssetContainer::GetInstance()->RequestTexture("Data/Resource/Texture/church_cubemap.dds");

		myRenderer = new Renderer(myFullscreenEffect);
		myRenderer->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });

		myPointLightInstance = AssetContainer::GetInstance()->LoadModel("Data/Resource/Model/Light_Mesh/SM_sphere.fbx", "Data/Resource/Shader/S_effect_deferred_pointlight.fx");
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
		RenderPointLights(aScene);
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

	void DeferredRenderer::RenderPointLights(Scene* aScene)
	{
		myRenderer->SetEffect(myPointLightEffect);
		myRenderer->SetTexture("AlbedoMetalnessTexture", myGBuffer->myAlbedoAndMetalness);
		myRenderer->SetTexture("NormalRoughnessTexture", myGBuffer->myNormalAndRoughness);
		myRenderer->SetTexture("DepthTexture", myGBuffer->myDepth);
		myRenderer->SetTexture("Cubemap", myCubemap);

		const CU::GrowingArray<PointLight*>& pointLights = aScene->GetPointLights();
		for each (const PointLight* light in pointLights)
		{
			myRenderer->SetRawData("PointLight", sizeof(light->GetData()), &light->GetData());
			myPointLightInstance->SetPosition(light->GetData().myPosition);
			myPointLightInstance->Render(myRenderer, aScene->GetCamera());
		}
	}

}