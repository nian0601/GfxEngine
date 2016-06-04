#include "stdafx.h"

#include <d3d11.h>
#include <D3DX11async.h>
#include <d3dx11effect.h>
#include "Effect.h"
#include "GPUContainer.h"
#include "Renderer.h"
#include "Texture.h"

namespace Easy3D
{
	Renderer::Renderer()
	{
		InitFullscreenQuad(GPUContainer::GetInstance()->RequestEffect("Data/Shader/S_effect_fullscreen.fx"));
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::SetEffect(Effect* aEffect)
	{
		myCurrentEffect = aEffect;
	}

	void Renderer::SetTexture(const CU::String<50>& aName, Texture* aTexture)
	{
		ID3DX11EffectVariable* var = GetEffectVariable(aName);
		var->AsShaderResource()->SetResource(aTexture->GetShaderView());
	}

	void Renderer::SetMatrix(const CU::String<50>& aName, const CU::Matrix44<float>& aMatrix)
	{
		ID3DX11EffectVariable* var = GetEffectVariable(aName);
		var->AsMatrix()->SetMatrix(&aMatrix.myMatrix[0]);
	}

	void Renderer::SetVector(const CU::String<50>& aName, const CU::Vector3<float>& aVector)
	{
		ID3DX11EffectVariable* var = GetEffectVariable(aName);
		var->AsVector()->SetFloatVector(&aVector.x);
	}

	void Renderer::SetVector(const CU::String<50>& aName, const CU::Vector4<float>& aVector)
	{
		ID3DX11EffectVariable* var = GetEffectVariable(aName);
		var->AsVector()->SetFloatVector(&aVector.x);
	}

	void Renderer::AddRenderTarget(Texture* aTexture)
	{
		DL_ASSERT_EXP(myRenderTargetCount < 4, CU::Concatenate<256>("Added to many RenderTargets, only %i supported", 4));
		myRenderTargets[myRenderTargetCount] = aTexture->GetRenderTarget();
		++myRenderTargetCount;
	}

	void Renderer::ClearRenderTarget(Texture* aTexture, const CU::Vector4<float>& aColor)
	{
		float clearColor[4];
		clearColor[0] = aColor.x;
		clearColor[1] = aColor.y;
		clearColor[2] = aColor.z;
		clearColor[3] = aColor.w;

		Engine::GetInstance()->GetContext()->ClearRenderTargetView(aTexture->GetRenderTarget(), clearColor);
	}

	void Renderer::SetDepthStencil(Texture* aTexture)
	{
		myDepthStencil = aTexture->GetDepthStencil();
	}

	void Renderer::ClearDepthStencil(Texture* aTexture)
	{
		Engine::GetInstance()->GetContext()->ClearDepthStencilView(aTexture->GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void Renderer::ApplyRenderTargetAndDepthStencil()
	{
		Engine::GetInstance()->GetContext()->OMSetRenderTargets(myRenderTargetCount, myRenderTargets, myDepthStencil);
		myRenderTargetCount = 0;
	}

	void Renderer::RenderFullScreen(const CU::String<30>& aTechnique)
	{
		ActivateFullscreenQuad();
		RenderFullscreenQuad(myCurrentEffect, aTechnique);
	}

	void Renderer::RenderModel(const ModelData& aData, const CU::String<30>& aTechnique)
	{
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();

		const unsigned int byteOffset = 0;

		context->IASetInputLayout(aData.myInputLayout);
		context->IASetVertexBuffers(0, 1, &aData.myVertexBuffer->myVertexBuffer, &aData.myVertexBuffer->myStride, &byteOffset);
		context->IASetIndexBuffer(aData.myIndexBuffer->myIndexBuffer, DXGI_FORMAT(aData.myIndexBuffer->myIndexBufferFormat), byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(aData.myPrimitiveTopology));

		D3DX11_TECHNIQUE_DESC techDesc;
		myCurrentEffect->GetTechnique(aTechnique)->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			myCurrentEffect->GetTechnique(aTechnique)->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(aData.myIndexData->myNumberOfIndices, 0, 0);
		}
	}

	ID3DX11EffectVariable* Renderer::GetEffectVariable(const CU::String<50>& aName)
	{
		DL_ASSERT_EXP(myCurrentEffect != nullptr, "Cant GetEffectVariable without an Effect");
		ID3DX11EffectVariable* var = myCurrentEffect->GetEffect()->GetVariableByName(aName.c_str());
		DL_ASSERT_EXP(var->IsValid() == TRUE, CU::Concatenate<256>("ShaderVar: %s not found", aName.c_str()));
		return var;
	}

}