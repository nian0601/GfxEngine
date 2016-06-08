#pragma once

#include <GrowingArray.h>
#include "EngineTypes.h"

struct ID3D11InputLayout;
struct D3D11_INPUT_ELEMENT_DESC;


namespace Easy3D
{
	struct VertexBuffer;
	struct VertexData;
	struct IndexBuffer;
	struct IndexData;

	class Texture;

	class GPUData
	{
		friend class FBXFactory;
		friend class Renderer;
	public:
		GPUData();
		~GPUData();

		void Init(EffectID aEffect);
		void Init(EffectID aEffect, int aIndexCount, char* aIndexData, int aVertexCount, int aVertexStride, char* aVertexData);
		void SetTopology(int aTopology);
		void AddInputElement(D3D11_INPUT_ELEMENT_DESC* aElement);

		const VertexBuffer& GetVertexBuffer() const;
		const IndexBuffer& GetIndexBuffer() const;
		ID3D11InputLayout* GetInputLayout() const;
		int GetTopology() const;


	private:
		void InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, EffectID aEffect);
		void InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage);
		void InitIndexBuffer();

		void SetupVertexBuffer(int aVertexCount, char* aVertexData);
		void SetupIndexBuffer(int aIndexCount, char* aIndexData);

		VertexBuffer* myVertexBuffer;
		VertexData* myVertexData;
		IndexBuffer* myIndexBuffer;
		IndexData* myIndexData;
		ID3D11InputLayout* myInputLayout;
		int myPrimitiveTopology;
		CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*> myVertexFormat;

		CU::GrowingArray<CU::String<50>> myShaderResourceNames;
		CU::GrowingArray<Texture*> myTextures;
	};

	inline const VertexBuffer& GPUData::GetVertexBuffer() const
	{
		return *myVertexBuffer;
	}

	inline const IndexBuffer& GPUData::GetIndexBuffer() const
	{
		return *myIndexBuffer;
	}

	inline ID3D11InputLayout* GPUData::GetInputLayout() const
	{
		return myInputLayout;
	}

	inline int GPUData::GetTopology() const
	{
		return myPrimitiveTopology;
	}
}