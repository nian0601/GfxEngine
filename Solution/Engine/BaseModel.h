#pragma once

#include <GrowingArray.h>

struct ID3D11InputLayout;
struct D3D11_INPUT_ELEMENT_DESC;

namespace Frost
{
	class Effect;

	struct VertexBuffer;
	struct VertexData;
	struct IndexBuffer;
	struct IndexData;

	class BaseModel
	{
	public:
		BaseModel();
		~BaseModel();

		virtual void Render(Effect& aEffect);

	protected:
		void InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, Effect* aEffect);
		void InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage);
		void InitIndexBuffer();

		void SetupVertexBuffer(int aVertexCount, char* aVertexData);
		void SetupIndexBuffer(int aIndexCount, char* aIndexData);

		VertexBuffer* myVertexBuffer;
		VertexData* myVertexData;
		IndexBuffer* myIndexBuffer;
		IndexData* myIndexData;
		ID3D11InputLayout* myInputLayout;
		CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*> myVertexFormat;
		int myPrimitiveTopology;

		bool myIsNullObject;
	};
}