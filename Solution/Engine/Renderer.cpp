#include "stdafx.h"

#include "AssetContainer.h"
#include <d3d11.h>
#include <D3DX11async.h>
#include <d3dx11effect.h>
#include "Effect.h"
#include "Renderer.h"
#include "Texture.h"
#include "GPUData.h"

namespace Easy3D
{
	Renderer::Renderer(EffectID aFullscreenEffect)
	{
		InitFullscreenQuad(aFullscreenEffect);
		Engine::GetInstance()->GetBackbuffer(myBackbuffer);
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::SetEffect(EffectID aEffect)
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

	void Renderer::SetClearColor(const CU::Vector4<float>& aColor)
	{
		myClearColor[0] = aColor.x;
		myClearColor[1] = aColor.y;
		myClearColor[2] = aColor.z;
		myClearColor[3] = aColor.w;
	}

	void Renderer::AddRenderTarget(Texture* aTexture)
	{
		DL_ASSERT_EXP(myRenderTargetCount < 4, CU::Concatenate<256>("Added to many RenderTargets, only %i supported", 4));
		myRenderTargets[myRenderTargetCount] = aTexture->GetRenderTarget();
		++myRenderTargetCount;
	}

	void Renderer::ClearRenderTarget(Texture* aTexture)
	{
		Engine::GetInstance()->GetContext()->ClearRenderTargetView(aTexture->GetRenderTarget(), myClearColor);
	}

	void Renderer::SetDepthStencil(Texture* aTexture)
	{
		myDepthStencil = aTexture->GetDepthStencil();
	}

	void Renderer::ClearDepthStencil(Texture* aTexture)
	{
		Engine::GetInstance()->GetContext()->ClearDepthStencilView(aTexture->GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void Renderer::SetBackbufferAsTarget()
	{
		DL_ASSERT_EXP(myRenderTargetCount < 4, CU::Concatenate<256>("Added to many RenderTargets, only %i supported", 4));
		myRenderTargets[myRenderTargetCount] = myBackbuffer.myBackbufferTarget;
		++myRenderTargetCount;
		myDepthStencil = myBackbuffer.myDepthStencilView;
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
		if (aData.myIsNullObject == false)
		{
			const GPUData& gpuData = *aData.myGPUData;
			for (int i = 0; i < gpuData.myTextures.Size(); ++i)
			{
				SetTexture(gpuData.myShaderResourceNames[i], gpuData.myTextures[i]);
			}
		
			RenderGPUData(gpuData, aTechnique);
		}

		for (ModelData* child : aData.myChildren)
		{
			RenderModel(*child, aTechnique);
		}
	}

	ID3DX11EffectVariable* Renderer::GetEffectVariable(const CU::String<50>& aName)
	{
		if (myEffectVariables[myCurrentEffect].KeyExists(aName) == false)
		{
			Effect* effect = AssetContainer::GetInstance()->GetEffect(myCurrentEffect);

			DL_ASSERT_EXP(effect != nullptr, "Cant GetEffectVariable without an Effect");
			ID3DX11EffectVariable* var = effect->GetEffect()->GetVariableByName(aName.c_str());
			DL_ASSERT_EXP(var->IsValid() == TRUE, CU::Concatenate<256>("ShaderVar: %s not found", aName.c_str()));
			
			myEffectVariables[myCurrentEffect][aName] = var;
		}

		return myEffectVariables[myCurrentEffect][aName];
	}

	void Renderer::RenderGPUData(const GPUData& someData, const CU::String<30>& aTechnique)
	{
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();

		const unsigned int byteOffset = 0;

		context->IASetInputLayout(someData.myInputLayout);
		context->IASetVertexBuffers(0, 1, &someData.myVertexBuffer->myVertexBuffer, &someData.myVertexBuffer->myStride, &byteOffset);
		context->IASetIndexBuffer(someData.myIndexBuffer->myIndexBuffer, DXGI_FORMAT(someData.myIndexBuffer->myIndexBufferFormat), byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(someData.myPrimitiveTopology));

		Effect* effect = AssetContainer::GetInstance()->GetEffect(myCurrentEffect);
		D3DX11_TECHNIQUE_DESC techDesc;
		effect->GetTechnique(aTechnique)->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			effect->GetTechnique(aTechnique)->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(someData.myIndexData->myNumberOfIndices, 0, 0);
		}
	}

}