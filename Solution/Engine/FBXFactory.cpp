#include "stdafx.h"


#include <CommonHelper.h>
#include <d3d11.h>
#include "FbxFactory.h"
#include "FBX/FbxLoader.h"
#include "Matrix44.h"
#include "Model.h"
#include "Surface.h"


namespace Easy3D
{
	FBXFactory::FBXFactory()
	{
		myLoader = new FBXLoader();
	}

	FBXFactory::~FBXFactory()
	{
		int DeleteFromMapHere = 5;
		/*
		for (auto it = myModels.begin(); it != myModels.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		myModels.clear();
		*/
		SAFE_DELETE(myLoader);
	}

	Model* FBXFactory::LoadModel(const CU::String<50>& aFilePath, Effect* aEffect)
	{
		if (myModels.KeyExists(aFilePath) == true)
		{
			return myModels[aFilePath];
		}

		CU::GrowingArray<CU::String<80>> errors(16);
		FbxModelData* fbxModelData = myLoader->loadModel(aFilePath.c_str(), errors);

		Model* returnModel = CreateModel(fbxModelData);
		myModels[aFilePath] = returnModel;

		returnModel->Init(aEffect);
		return returnModel;
	}

	Model* FBXFactory::CreateModel(FbxModelData* someModelData)
	{
		Model* tempModel = new Model();
		tempModel->myPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		if (someModelData->myData)
		{
			tempModel->myIsNullObject = false;

			IndexData* indexData = new IndexData();
			VertexData* vertexData = new VertexData();
			Surface* surface = new Surface();

			LoadData(indexData, vertexData, tempModel->myVertexFormat, *surface
				, someModelData->myData);

			tempModel->mySurfaces.Add(surface);
			tempModel->myIndexData = indexData;
			tempModel->myVertexData = vertexData;
			tempModel->myOrientation = someModelData->myOrientation;
		}

		for (int i = 0; i < someModelData->myChildren.Size(); ++i)
		{
			auto currentChild = someModelData->myChildren[i];
			tempModel->AddChild(CreateModel(currentChild));
		}
		return tempModel;
	}

	void FBXFactory::LoadData(IndexData* aIndexWrapper, VertexData* aVertexData
		, CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*>& someInputElements, Surface& aSurface
		, ModelData* someData)
	{
		aIndexWrapper->myFormat = DXGI_FORMAT_R32_UINT;
		unsigned int* indexData = new unsigned int[someData->myIndexCount];
		memcpy(indexData, someData->myIndicies, someData->myIndexCount*sizeof(unsigned int));
		aIndexWrapper->myIndexData = (char*)indexData;
		aIndexWrapper->mySize = someData->myIndexCount*sizeof(unsigned int);
		aIndexWrapper->myNumberOfIndices = someData->myIndexCount;

		int sizeOfBuffer = someData->myVertexCount*someData->myVertexStride*sizeof(float);
		char* vertexRawData = new char[sizeOfBuffer];
		memcpy(vertexRawData, someData->myVertexBuffer, sizeOfBuffer);
		aVertexData->myVertexData = vertexRawData;
		aVertexData->myNumberOfVertices = someData->myVertexCount;
		aVertexData->mySize = sizeOfBuffer;
		aVertexData->myStride = someData->myVertexStride*sizeof(float);

		for (int i = 0; i < someData->myLayout.Size(); ++i)
		{
			auto currentLayout = someData->myLayout[i];
			D3D11_INPUT_ELEMENT_DESC* desc = new D3D11_INPUT_ELEMENT_DESC();
			desc->SemanticIndex = currentLayout.mySemanticIndex;
			desc->AlignedByteOffset = currentLayout.myOffset;
			desc->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc->InputSlot = 0;
			desc->InstanceDataStepRate = 0;

			if (currentLayout.myType == ModelData::VERTEX_POS)
			{
				desc->SemanticName = "POSITION";
				desc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_NORMAL)
			{
				desc->SemanticName = "NORMAL";
				desc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_UV)
			{
				desc->SemanticName = "TEXCOORD";
				desc->Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_BINORMAL)
			{
				desc->SemanticName = "BINORMAL";
				desc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_TANGENT)
			{
				desc->SemanticName = "TANGENT";
				desc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_SKINWEIGHTS)
			{
				desc->SemanticName = "WEIGHTS";
				desc->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_BONEID)
			{
				desc->SemanticName = "BONES";
				desc->Format = DXGI_FORMAT_R32G32B32A32_UINT;
			}
			else if (currentLayout.myType == ModelData::VERTEX_COLOR)
			{
				desc->SemanticName = "COLOR";
				desc->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
			someInputElements.Add(desc);
		}

		for (int i = 0; i < someData->myTextures.Size(); ++i)
		{
			auto& currentTexture = someData->myTextures[i];

			CU::String<80> resourceName;
			if (currentTexture.myType == ALBEDO)
			{
				resourceName = "AlbedoTexture";
			}
			if (currentTexture.myType == NORMAL)
			{
				resourceName = "NormalTexture";
			}
			if (currentTexture.myType == ROUGHNESS)
			{
				resourceName = "RoughnessTexture";
			}
			if (currentTexture.myType == METALNESS)
			{
				resourceName = "MetalnessTexture";
			}
			if (currentTexture.myType == AMBIENT)
			{
				resourceName = "AOTexture";
			}
			if (currentTexture.myType == FBXTextureType::EMISSIVE)
			{
				resourceName = "EmissiveTexture";
			}

			int dataIndex = currentTexture.myFileName.RFind("Data\\");
			CU::String<256> fromData = currentTexture.myFileName.SubStr(dataIndex, currentTexture.myFileName.Size());

			aSurface.AddTexture(fromData.c_str(), resourceName.c_str());
		}
	}
}