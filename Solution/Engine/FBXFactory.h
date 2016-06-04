#pragma once

#include "IModelFactory.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include <CUMap.h>

struct D3D11_INPUT_ELEMENT_DESC;

namespace FBX
{
	struct AnimationData;
	struct Bone;
	struct ModelData;

	class FBXLoader;
	class FbxModelData;
}

namespace Easy3D
{
	class Model;
	class Surface;

	class FBXFactory : public IModelFactory
	{
	public:
		FBXFactory();
		~FBXFactory();

		Model* LoadModel(const CU::String<50>& aFilePath, Effect* aEffect) override;
		
	private:
		Model* CreateModel(FBX::FbxModelData* someModelData);
		void LoadData(IndexData* aIndexWrapper, VertexData* aVertexData
			, CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*>& someInputElements, Surface& aSurface
			, FBX::ModelData* someData);

		

		FBX::FBXLoader *myLoader;

		CU::Map<CU::String<50>, Model*> myModels;
	};
}