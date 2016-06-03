#pragma once

#include "IModelFactory.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include <CUMap.h>

struct AnimationData;
struct Bone;
struct ModelData;
struct D3D11_INPUT_ELEMENT_DESC;

class FBXLoader;
class FbxModelData;

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
		Model* CreateModel(FbxModelData* someModelData);
		void LoadData(IndexData* aIndexWrapper, VertexData* aVertexData
			, CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*>& someInputElements, Surface& aSurface
			, ModelData* someData);

		

		FBXLoader *myLoader;

		CU::Map<CU::String<50>, Model*> myModels;
	};
}