#include "stdafx.h"

#include <d3dx11effect.h>
#include "FullscreenQuad.h"
#include "GPUData.h"
#include "GPUContainer.h"
#include "Effect.h"


namespace Easy3D
{
	FullscreenQuad::FullscreenQuad()
	{
	}


	FullscreenQuad::~FullscreenQuad()
	{
	}

	void FullscreenQuad::InitFullscreenQuad(EffectID aEffect)
	{
		CU::GrowingArray<VertexPosUV> vertices(4);
		vertices.Add({ { -1.f, -1.f, 0.f }, { 0.f, 1.f } }); //topleft
		vertices.Add({ { 1.f, -1.f, 0.f }, { 1.f, 1.f } }); //topright
		vertices.Add({ { -1.f, 1.f, 0.f }, { 0.f, 0.f } }); //bottomleft
		vertices.Add({ { 1.f, 1.f, 0.f }, { 1.f, 0.f } }); //bottomright


		CU::GrowingArray<int> indices(6);
		indices.Add(0);
		indices.Add(2);
		indices.Add(1);

		indices.Add(1);
		indices.Add(2);
		indices.Add(3);


		myGPUData.SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		myGPUData.AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }));
		myGPUData.AddInputElement(new D3D11_INPUT_ELEMENT_DESC({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }));
		myGPUData.Init(aEffect, indices.Size(), reinterpret_cast<char*>(&indices[0]), vertices.Size()
			, sizeof(VertexPosUV), reinterpret_cast<char*>(&vertices[0]));
	}

	void FullscreenQuad::ActivateFullscreenQuad()
	{
		const unsigned int byteOffset = 0;
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();
		const IndexBuffer& indexBuffer = myGPUData.GetIndexBuffer();
		const VertexBuffer& vertexBuffer = myGPUData.GetVertexBuffer();

		context->IASetInputLayout(myGPUData.GetInputLayout());
		context->IASetIndexBuffer(indexBuffer.myIndexBuffer, DXGI_FORMAT(indexBuffer.myIndexBufferFormat), byteOffset);
		context->IASetVertexBuffers(0, 1, &vertexBuffer.myVertexBuffer, &vertexBuffer.myStride, &byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(myGPUData.GetTopology()));
	}

	void FullscreenQuad::RenderFullscreenQuad(EffectID aEffect, const CU::String<30>& aTechnique)
	{
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();
		Effect* effect = GPUContainer::GetInstance()->GetEffect(aEffect);

		D3DX11_TECHNIQUE_DESC techDesc;
		effect->GetTechnique(aTechnique)->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			effect->GetTechnique(aTechnique)->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(6, 0, 0);
		}
	}

}