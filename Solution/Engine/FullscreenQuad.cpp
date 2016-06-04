#include "stdafx.h"

#include <d3dx11effect.h>
#include "FullscreenQuad.h"
#include "GfxStructs.h"


namespace Easy3D
{
	FullscreenQuad::FullscreenQuad()
	{
	}


	FullscreenQuad::~FullscreenQuad()
	{
	}

	void FullscreenQuad::InitFullscreenQuad(Effect* aEffect)
	{
		D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		InitInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), aEffect);
		InitVertexBuffer(sizeof(VertexPosUV), D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		CU::GrowingArray<VertexPosUV> vertices;
		vertices.Init(4);
		vertices.Add({ { -1.f, -1.f, 0.f }, { 0.f, 1.f } }); //topleft
		vertices.Add({ { 1.f, -1.f, 0.f }, { 1.f, 1.f } }); //topright
		vertices.Add({ { -1.f, 1.f, 0.f }, { 0.f, 0.f } }); //bottomleft
		vertices.Add({ { 1.f, 1.f, 0.f }, { 1.f, 0.f } }); //bottomright

		CU::GrowingArray<int> indices;
		indices.Init(6);

		indices.Add(0);
		indices.Add(2);
		indices.Add(1);

		indices.Add(1);
		indices.Add(2);
		indices.Add(3);

		SetupVertexBuffer(vertices.Size(), reinterpret_cast<char*>(&vertices[0]));
		SetupIndexBuffer(indices.Size(), reinterpret_cast<char*>(&indices[0]));

		myData.myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}

	void FullscreenQuad::ActivateFullscreenQuad()
	{
		const unsigned int byteOffset = 0;
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();
		context->IASetInputLayout(myData.myInputLayout);
		context->IASetVertexBuffers(0, 1, &myData.myVertexBuffer->myVertexBuffer, &myData.myVertexBuffer->myStride, &byteOffset);
		context->IASetIndexBuffer(myData.myIndexBuffer->myIndexBuffer, DXGI_FORMAT(myData.myIndexBuffer->myIndexBufferFormat), byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(myData.myPrimitiveTopology));
	}

	void FullscreenQuad::RenderFullscreenQuad(Effect* aEffect, const CU::String<30>& aTechnique)
	{
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();

		D3DX11_TECHNIQUE_DESC techDesc;
		aEffect->GetTechnique(aTechnique)->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			aEffect->GetTechnique(aTechnique)->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(6, 0, 0);
		}
	}

}