#pragma once


struct ID3D11InputLayout;
struct D3D11_INPUT_ELEMENT_DESC;

namespace Frost
{
	class Effect;

	struct VertexBuffer;
	struct IndexBuffer;

	class BaseModel
	{
	public:
		BaseModel();
		~BaseModel();

		virtual void Render(Effect& aEffect);

	protected:
		void InitInputLayout(D3D11_INPUT_ELEMENT_DESC* aVertexDescArray, int aArraySize, Effect& aEffect);
		void InitVertexBuffer(int aVertexSize, int aBufferUsage, int aCPUUsage);
		void InitIndexBuffer();

		void SetupVertexBuffer(int aVertexCount, char* aVertexData);
		void SetupIndexBuffer(int aIndexCount, char* aIndexData);

		VertexBuffer* myVertexBuffer;
		IndexBuffer* myIndexBuffer;
		ID3D11InputLayout* myInputLayout;
	};
}