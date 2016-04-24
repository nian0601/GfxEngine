#include "stdafx.h"

#include <D3DX11tex.h>
#include "Effect.h"
#include "GBuffer.h"
#include "Texture.h"


namespace Frost
{
	GBuffer::GBuffer()
	{
		CU::Vector2<float> windowSize = Engine::GetInstance()->GetWindowSize();

		myAlbedoAndMetalness = new Texture();
		myAlbedoAndMetalness->InitForShader(windowSize.x, windowSize.y
			, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
			, DXGI_FORMAT_R32G32B32A32_FLOAT);

		myNormalAndRoughness = new Texture();
		myNormalAndRoughness->InitForShader(windowSize.x, windowSize.y
			, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
			, DXGI_FORMAT_R32G32B32A32_FLOAT);

		myDepth = new Texture();
		myDepth->InitForShader(windowSize.x, windowSize.y
			, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE
			, DXGI_FORMAT_R32_FLOAT);

		myDepthStencil = new Texture();
		myDepthStencil->InitForShader(windowSize.x, windowSize.y
			, D3D11_BIND_DEPTH_STENCIL
			, DXGI_FORMAT_R32_TYPELESS);
	}


	GBuffer::~GBuffer()
	{
		SAFE_DELETE(myAlbedoAndMetalness);
		SAFE_DELETE(myNormalAndRoughness);
		SAFE_DELETE(myDepth);
	}

	void GBuffer::Set(Effect* aEffect)
	{
		aEffect->SetAlbedoMetalness(myAlbedoAndMetalness->GetShaderView());
		aEffect->SetNormalRoughness(myNormalAndRoughness->GetShaderView());
		aEffect->SetDepth(myDepth->GetShaderView());
	}

	void GBuffer::UnSet(Effect* aEffect)
	{
		aEffect->SetAlbedoMetalness(nullptr);
		aEffect->SetNormalRoughness(nullptr);
		aEffect->SetDepth(nullptr);
	}

	void GBuffer::Clear(const CU::Vector4<float>& aColor)
	{
		float clearColor[4];
		clearColor[0] = aColor.x;
		clearColor[1] = aColor.y;
		clearColor[2] = aColor.z;
		clearColor[3] = aColor.w;

		Engine::GetInstance()->GetContext()->ClearRenderTargetView(myAlbedoAndMetalness->GetRenderTarget(), clearColor);
		Engine::GetInstance()->GetContext()->ClearRenderTargetView(myNormalAndRoughness->GetRenderTarget(), clearColor);
		Engine::GetInstance()->GetContext()->ClearRenderTargetView(myDepth->GetRenderTarget(), clearColor);

		Engine::GetInstance()->GetContext()->ClearDepthStencilView(myDepthStencil->GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void GBuffer::Resize(float aWidth, float aHeight)
	{
		myAlbedoAndMetalness->Resize(aWidth, aHeight);
		myNormalAndRoughness->Resize(aWidth, aHeight);
		myDepth->Resize(aWidth, aHeight);
	}

}