#include "stdafx.h"
#include "BaseModel.h"
#include <d3dx11effect.h>
#include <d3d11.h>
#include "GfxStructs.h"

namespace Easy3D
{
	BaseModel::BaseModel()
		: myVertexFormat(5)
		, myIsNullObject(true)
	{
		myData.myVertexBuffer = nullptr;
		myData.myVertexData = nullptr;
		myData.myIndexBuffer = nullptr;
		myData.myIndexData = nullptr;
	}


	BaseModel::~BaseModel()
	{
		SAFE_DELETE(myData.myVertexBuffer);
		SAFE_DELETE(myData.myVertexData);
		SAFE_DELETE(myData.myIndexBuffer);
		SAFE_DELETE(myData.myIndexData);
	}

	void BaseModel::Render(Effect& aEffect)
	{
		ID3D11DeviceContext* context = Engine::GetInstance()->GetContext();

		const unsigned int byteOffset = 0;

		context->IASetInputLayout(myData.myInputLayout);
		context->IASetVertexBuffers(0, 1, &myData.myVertexBuffer->myVertexBuffer, &myData.myVertexBuffer->myStride, &byteOffset);
		context->IASetIndexBuffer(myData.myIndexBuffer->myIndexBuffer, DXGI_FORMAT(myData.myIndexBuffer->myIndexBufferFormat), byteOffset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(myData.myPrimitiveTopology));

		D3DX11_TECHNIQUE_DESC techDesc;
		aEffect.GetTechnique("Render")->GetDesc(&techDesc);
		for (UINT i = 0; i < techDesc.Passes; ++i)
		{
			aEffect.GetTechnique("Render")->GetPassByIndex(i)->Apply(0, context);
			context->DrawIndexed(myData.myIndexData->myNumberOfIndices, 0, 0);
		}
	}

	void BaseModel::InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, Effect* aEffect)
	{
		D3DX11_PASS_DESC passDesc;
		aEffect->GetTechnique("Render")->GetPassByIndex(0)->GetDesc(&passDesc);
		HRESULT hr = Engine::GetInstance()->GetDevice()->CreateInputLayout(aVertexDescArray
			, aArraySize, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &myData.myInputLayout);
		if (FAILED(hr) != S_OK)
		{
			DL_MESSAGE_BOX("Failed to CreateInputLayout", "BaseModel::Init", MB_ICONWARNING);
		}
	}

	void BaseModel::InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage)
	{
		myData.myVertexBuffer = new VertexBuffer();
		myData.myVertexBuffer->myStride = aVertexSize;

		myData.myVertexBuffer->myBufferDesc = new D3D11_BUFFER_DESC();
		ZeroMemory(myData.myVertexBuffer->myBufferDesc, sizeof(*myData.myVertexBuffer->myBufferDesc));
		myData.myVertexBuffer->myBufferDesc->Usage = D3D11_USAGE(aBufferUsage);
		myData.myVertexBuffer->myBufferDesc->BindFlags = D3D11_BIND_VERTEX_BUFFER;
		myData.myVertexBuffer->myBufferDesc->CPUAccessFlags = aCPUUsage;
		myData.myVertexBuffer->myBufferDesc->MiscFlags = 0;
		myData.myVertexBuffer->myBufferDesc->StructureByteStride = 0;
	}

	void BaseModel::InitIndexBuffer()
	{
		myData.myIndexBuffer = new IndexBuffer();
		myData.myIndexBuffer->myIndexBufferFormat = DXGI_FORMAT_R32_UINT;

		myData.myIndexBuffer->myBufferDesc = new D3D11_BUFFER_DESC();
		ZeroMemory(myData.myIndexBuffer->myBufferDesc, sizeof(*myData.myIndexBuffer->myBufferDesc));
		myData.myIndexBuffer->myBufferDesc->Usage = D3D11_USAGE_IMMUTABLE;
		myData.myIndexBuffer->myBufferDesc->BindFlags = D3D11_BIND_INDEX_BUFFER;
		myData.myIndexBuffer->myBufferDesc->CPUAccessFlags = 0;
		myData.myIndexBuffer->myBufferDesc->MiscFlags = 0;
		myData.myIndexBuffer->myBufferDesc->StructureByteStride = 0;
	}

	void BaseModel::SetupVertexBuffer(int aVertexCount, char* aVertexData)
	{
		if (myData.myVertexBuffer->myVertexBuffer != nullptr)
		{
			SAFE_RELEASE(myData.myVertexBuffer->myVertexBuffer);
		}

		myData.myVertexBuffer->myBufferDesc->ByteWidth = myData.myVertexBuffer->myStride * aVertexCount;
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = aVertexData;

		DL_ASSERT_EXP(SUCCEEDED(Engine::GetInstance()->GetDevice()->CreateBuffer(myData.myVertexBuffer->myBufferDesc, &initData
			, &myData.myVertexBuffer->myVertexBuffer)) == TRUE, "BaseModel::SetupVertexBuffer: Failed to SetupVertexBuffer");
	}

	void BaseModel::SetupIndexBuffer(int aIndexCount, char* aIndexData)
	{
		if (myData.myIndexBuffer->myIndexBuffer != nullptr)
		{
			SAFE_RELEASE(myData.myIndexBuffer->myIndexBuffer);
		}

		myData.myIndexBuffer->myBufferDesc->ByteWidth = sizeof(UINT) * aIndexCount;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = aIndexData;

		DL_ASSERT_EXP(SUCCEEDED(Engine::GetInstance()->GetDevice()->CreateBuffer(myData.myIndexBuffer->myBufferDesc, &initData,
			&myData.myIndexBuffer->myIndexBuffer)) == TRUE, "BaseModel::SetupIndexBuffer: Failed to SetupIndexBuffer");
	}
}