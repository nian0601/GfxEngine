#include "stdafx.h"
#include "Model.h"
#include <d3dx11effect.h>
#include <GrowingArray.h>
#include "Surface.h"

namespace Frost
{
	Model::Model()
		: myChildren(4)
		, myChildTransforms(4)
		, mySurfaces(4)
	{
	}


	Model::~Model()
	{
	}

	void Model::AddChild(Model* aModel)
	{
		myChildren.Add(aModel);
		myChildTransforms.Add(aModel->myOrientation);
	}

	void Model::Init(Effect* aEffect)
	{
		if (myIsNullObject == false)
		{
			const int size = myVertexFormat.Size();
			D3D11_INPUT_ELEMENT_DESC* vertexDesc = new D3D11_INPUT_ELEMENT_DESC[size];
			for (int i = 0; i < myVertexFormat.Size(); ++i)
			{
				vertexDesc[i] = *myVertexFormat[i];
			}

			InitInputLayout(vertexDesc, size, aEffect);

			InitVertexBuffer(myVertexData->myStride, D3D11_USAGE_IMMUTABLE, 0);
			InitIndexBuffer();

			SetupVertexBuffer(myVertexData->myNumberOfVertices, myVertexData->myVertexData);
			SetupIndexBuffer(myIndexData->myNumberOfIndices, myIndexData->myIndexData);

			for (Surface* surface : mySurfaces)
			{
				surface->GetShaderResources(aEffect);
			}
		}

		for (Model* child : myChildren)
		{
			child->Init(aEffect);
		}
	}

	void Model::InitCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect* aEffect)
	{
		myIsNullObject = false;

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

		myIndexData = new IndexData();
		myIndexData->myIndexData = reinterpret_cast<char*>(&indices[0]);
		myIndexData->myNumberOfIndices = indices.Size();

		myVertexData = new VertexData();
		myVertexData->myVertexData = reinterpret_cast<char*>(&vertices[0]);
		myVertexData->myStride = sizeof(VertexPosColor);
		myVertexData->myNumberOfVertices = vertices.Size();

		InitVertexBuffer(myVertexData->myStride, D3D11_USAGE_IMMUTABLE, 0);
		InitIndexBuffer();

		SetupVertexBuffer(myVertexData->myNumberOfVertices, myVertexData->myVertexData);
		SetupIndexBuffer(myIndexData->myNumberOfIndices, myIndexData->myIndexData);
	}

	void Model::Render(Effect& aEffect)
	{
		if (myIsNullObject == false)
		{
			if (mySurfaces.Size() > 0)
			{
				mySurfaces[0]->Activate();
			}

			BaseModel::Render(aEffect);

			if (mySurfaces.Size() > 0)
			{
				mySurfaces[0]->Deactivate();
			}
		}

		for (Model* child : myChildren)
		{
			child->Render(aEffect);
		}
	}
}