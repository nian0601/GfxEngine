#include "stdafx.h"
#include "BaseModel.h"
#include <d3dx11effect.h>
#include <d3d11.h>
#include "GfxStructs.h"

namespace Frost
{
	BaseModel::BaseModel()
		: myVertexBuffer(nullptr)
		, myIndexBuffer(nullptr)
	{
	}


	BaseModel::~BaseModel()
	{
	}

	void BaseModel::Render(Effect& aEffect)
	{
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();

		const unsigned int byteOffset = 0;

		context->IASetInputLayout(myInputLayout);
		context->IASetVertexBuffers(0, 1, &myVertexBuffer->myVertexBuffer, &myVertexBuffer->myStride, &byteOffset);
		context->IASetIndexBuffer(myIndexBuffer->myIndexBuffer, DXGI_FORMAT(myIndexBuffer->myIndexBufferFormat), byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3DX11_TECHNIQUE_DESC techDesc;
		aEffect.GetTechnique("Render")->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			aEffect.GetTechnique("Render")->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(36, 0, 0);
		}
	}

	void BaseModel::InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, Effect& aEffect)
	{
		D3DX11_PASS_DESC passDesc;
		aEffect.GetTechnique("Render")->GetPassByIndex(0)->GetDesc(&passDesc);
		HRESULT hr = Engine::GetInstance()->GetDevice()->CreateInputLayout(aVertexDescArray
			, aArraySize, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &myInputLayout);
		if (FAILED(hr) != S_OK)
		{
			DL_MESSAGE_BOX("Failed to CreateInputLayout", "BaseModel::Init", MB_ICONWARNING);
		}

	}

	void BaseModel::InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage)
	{
		myVertexBuffer = new VertexBuffer();
		myVertexBuffer->myStride = aVertexSize;

		myVertexBuffer->myBufferDesc = new D3D11_BUFFER_DESC();
		ZeroMemory(myVertexBuffer->myBufferDesc, sizeof(*myVertexBuffer->myBufferDesc));
		myVertexBuffer->myBufferDesc->Usage = D3D11_USAGE(aBufferUsage);
		myVertexBuffer->myBufferDesc->BindFlags = D3D11_BIND_VERTEX_BUFFER;
		myVertexBuffer->myBufferDesc->CPUAccessFlags = aCPUUsage;
		myVertexBuffer->myBufferDesc->MiscFlags = 0;
		myVertexBuffer->myBufferDesc->StructureByteStride = 0;
	}

	void BaseModel::InitIndexBuffer()
	{
		myIndexBuffer = new IndexBuffer();
		myIndexBuffer->myIndexBufferFormat = DXGI_FORMAT_R32_UINT;

		myIndexBuffer->myBufferDesc = new D3D11_BUFFER_DESC();
		ZeroMemory(myIndexBuffer->myBufferDesc, sizeof(*myIndexBuffer->myBufferDesc));
		myIndexBuffer->myBufferDesc->Usage = D3D11_USAGE_IMMUTABLE;
		myIndexBuffer->myBufferDesc->BindFlags = D3D11_BIND_INDEX_BUFFER;
		myIndexBuffer->myBufferDesc->CPUAccessFlags = 0;
		myIndexBuffer->myBufferDesc->MiscFlags = 0;
		myIndexBuffer->myBufferDesc->StructureByteStride = 0;
	}

	void BaseModel::SetupVertexBuffer(int aVertexCount, char* aVertexData)
	{
		if (myVertexBuffer->myVertexBuffer != nullptr)
		{
			SAFE_RELEASE(myVertexBuffer->myVertexBuffer);
		}

		myVertexBuffer->myBufferDesc->ByteWidth = myVertexBuffer->myStride * aVertexCount;
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = aVertexData;

		DL_ASSERT_EXP(SUCCEEDED(Engine::GetInstance()->GetDevice()->CreateBuffer(myVertexBuffer->myBufferDesc, &initData
			, &myVertexBuffer->myVertexBuffer)) == TRUE, "BaseModel::SetupVertexBuffer: Failed to SetupVertexBuffer");
	}

	void BaseModel::SetupIndexBuffer(int aIndexCount, char* aIndexData)
	{
		if (myIndexBuffer->myIndexBuffer != nullptr)
		{
			SAFE_RELEASE(myIndexBuffer->myIndexBuffer);
		}

		myIndexBuffer->myBufferDesc->ByteWidth = sizeof(UINT) * aIndexCount;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = aIndexData;

		DL_ASSERT_EXP(SUCCEEDED(Engine::GetInstance()->GetDevice()->CreateBuffer(myIndexBuffer->myBufferDesc, &initData,
			&myIndexBuffer->myIndexBuffer)) == TRUE, "BaseModel::SetupIndexBuffer: Failed to SetupIndexBuffer");
	}
}