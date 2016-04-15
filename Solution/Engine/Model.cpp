#include "stdafx.h"
#include "Model.h"
#include <d3dx11effect.h>
#include <GrowingArray.h>

namespace Frost
{
	Model::Model()
	{
	}


	Model::~Model()
	{
	}

	void Model::InitTriangle(Effect& aEffect)
	{
		D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		InitInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), aEffect);

		CU::GrowingArray<VertexPosColor> vertices(4);
		vertices.Add({ { 0.0f, 0.5f, 0.5f, 0.f }, { 1.f, 0.f, 0.f, 1.f } });
		vertices.Add({ { 0.5f, -0.5f, 0.5, 0.f }, { 0.f, 1.f, 0.f, 1.f } });
		vertices.Add({ { -0.5f, -0.5f, 0.5f, 0.f }, { 0.f, 0.f, 1.f, 1.f } });


		CU::GrowingArray<int> indices(24);
		indices.Add(0);
		indices.Add(1);
		indices.Add(2);

		InitVertexBuffer(sizeof(VertexPosColor), D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		SetupVertexBuffer(vertices.Size(), reinterpret_cast<char*>(&vertices[0]));
		SetupIndexBuffer(indices.Size(), reinterpret_cast<char*>(&indices[0]));
	}

	void Model::InitCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect& aEffect)
	{
		D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		InitInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), aEffect);

#pragma region Vertices
		CU::GrowingArray<VertexPosColor> vertices;
		vertices.Init(8);

		float halfWidth = aSize.x / 2.f;
		float halfHeight = aSize.y / 2.f;
		float halfDepth = aSize.z / 2.f;

		vertices.Add({ { -halfWidth, halfHeight, -halfDepth, 1.f }, aColor });
		vertices.Add({ { halfWidth, halfHeight, -halfDepth, 1.f }, aColor });
		vertices.Add({ { halfWidth, halfHeight, halfDepth, 1.f }, aColor });
		vertices.Add({ { -halfWidth, halfHeight, halfDepth, 1.f }, aColor });
		vertices.Add({ { -halfWidth, -halfHeight, -halfDepth, 1.f }, aColor });
		vertices.Add({ { halfWidth, -halfHeight, -halfDepth, 1.f }, aColor });
		vertices.Add({ { halfWidth, -halfHeight, halfDepth, 1.f }, aColor });
		vertices.Add({ { -halfWidth, -halfHeight, halfDepth, 1.f }, aColor });
#pragma endregion

#pragma region Indices
		CU::GrowingArray<int> indices;
		indices.Init(24);

		indices.Add(3);
		indices.Add(1);
		indices.Add(0);

		indices.Add(2);
		indices.Add(1);
		indices.Add(3);

		indices.Add(0);
		indices.Add(5);
		indices.Add(4);

		indices.Add(1);
		indices.Add(5);
		indices.Add(0);

		indices.Add(3);
		indices.Add(4);
		indices.Add(7);

		indices.Add(0);
		indices.Add(4);
		indices.Add(3);

		indices.Add(1);
		indices.Add(6);
		indices.Add(5);

		indices.Add(2);
		indices.Add(6);
		indices.Add(1);

		indices.Add(2);
		indices.Add(7);
		indices.Add(6);

		indices.Add(3);
		indices.Add(7);
		indices.Add(2);

		indices.Add(6);
		indices.Add(4);
		indices.Add(5);

		indices.Add(7);
		indices.Add(4);
		indices.Add(6);
#pragma endregion


		InitVertexBuffer(sizeof(VertexPosColor), D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		SetupVertexBuffer(vertices.Size(), reinterpret_cast<char*>(&vertices[0]));
		SetupIndexBuffer(indices.Size(), reinterpret_cast<char*>(&indices[0]));
	}

	void Model::Render(Effect& aEffect)
	{
		BaseModel::Render(aEffect);
	}
}