#include "stdafx.h"
#include "Model.h"
#include <d3dx11effect.h>
#include <GrowingArray.h>

Model::Model()
{
	myOrientation.SetPos({ 0.f, 0.f, 2.f });
	myView.SetPos({ 0.f, 0.5f, -1.f });
	myProjection = CU::Matrix44<float>::CreateProjectionMatrixLH(0.1f, 100.f, static_cast<float>(1280.f) / static_cast<float>(720.f), PI);

}


Model::~Model()
{
}

void Model::InitCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect* aEffect)
{
	myEffect = aEffect;


	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	InitInputLayout(vertexDesc, ARRAYSIZE(vertexDesc));

#pragma region Vertices
	CU::GrowingArray<VertexPosColor> vertices;
	vertices.Init(24);

	float halfWidth = aSize.x / 2.f;
	float halfHeight = aSize.y / 2.f;
	float halfDepth = aSize.z / 2.f;

	//0 - 3 (Top)
	vertices.Add({ { -halfWidth, halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, halfHeight, halfDepth, 0.f }, aColor });

	//4 - 7 (Bottom)
	vertices.Add({ { -halfWidth, -halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, -halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, -halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, -halfHeight, halfDepth, 0.f }, aColor });

	//8 - 11 (Left)
	vertices.Add({ { -halfWidth, -halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, -halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, halfHeight, halfDepth, 0.f }, aColor });

	//12 - 15 (Right)
	vertices.Add({ { halfWidth, -halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, -halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, halfHeight, halfDepth, 0.f }, aColor });

	//16 - 19 (Front)
	vertices.Add({ { -halfWidth, -halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, -halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, halfHeight, -halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, halfHeight, -halfDepth, 0.f }, aColor });

	//20 - 23 (Back)
	vertices.Add({ { -halfWidth, -halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, -halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { halfWidth, halfHeight, halfDepth, 0.f }, aColor });
	vertices.Add({ { -halfWidth, halfHeight, halfDepth, 0.f }, aColor });
#pragma endregion

#pragma region Indices

	CU::GrowingArray<int> indices(24);
	//Top
	indices.Add(3);
	indices.Add(1);
	indices.Add(0);

	indices.Add(2);
	indices.Add(1);
	indices.Add(3);

	//Bottom
	indices.Add(6);
	indices.Add(4);
	indices.Add(5);

	indices.Add(7);
	indices.Add(4);
	indices.Add(6);

	//Left
	indices.Add(11);
	indices.Add(9);
	indices.Add(8);

	indices.Add(10);
	indices.Add(9);
	indices.Add(11);

	//Right
	indices.Add(14);
	indices.Add(12);
	indices.Add(13);

	indices.Add(15);
	indices.Add(12);
	indices.Add(14);

	//Front
	indices.Add(19);
	indices.Add(17);
	indices.Add(16);

	indices.Add(18);
	indices.Add(17);
	indices.Add(19);

	//Back
	indices.Add(22);
	indices.Add(20);
	indices.Add(21);

	indices.Add(23);
	indices.Add(20);
	indices.Add(22);

#pragma endregion


	InitVertexBuffer(sizeof(VertexPosColor), D3D11_USAGE_IMMUTABLE, 0);
	InitIndexBuffer();

	SetupVertexBuffer(vertices.Size(), reinterpret_cast<char*>(&vertices[0]));
	SetupIndexBuffer(indices.Size(), reinterpret_cast<char*>(&indices[0]));
}

void Model::Render()
{
	myEffect->SetWorldMatrix(myOrientation);
	myEffect->SetViewMatrix(myView);
	myEffect->SetProjectionMatrix(myProjection);

	BaseModel::Render();
}
