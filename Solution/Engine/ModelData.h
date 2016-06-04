#pragma once

struct ID3D11InputLayout;

namespace Easy3D
{
	struct VertexBuffer;
	struct VertexData;
	struct IndexBuffer;
	struct IndexData;

	struct ModelData
	{
		VertexBuffer* myVertexBuffer;
		VertexData* myVertexData;
		IndexBuffer* myIndexBuffer;
		IndexData* myIndexData;
		ID3D11InputLayout* myInputLayout;
		int myPrimitiveTopology;
	};
}