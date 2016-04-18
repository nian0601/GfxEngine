#pragma once

#include "IModelFactory.h"
#include "GfxStructs.h"
#include <GrowingArray.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <Vector.h>

struct AnimationData;
struct Bone;
struct ModelData;
struct D3D11_INPUT_ELEMENT_DESC;

class FBXLoader;
class FbxModelData;

namespace Frost
{
	class Model;
	class Surface;

	class FBXFactory : public IModelFactory
	{
	public:
		FBXFactory();
		~FBXFactory();

		Model* LoadModel(const std::string& aFilePath, Effect* aEffect) override;
		
	private:
		Model* CreateModel(FbxModelData* someModelData);
		void LoadData(IndexData* aIndexWrapper, VertexData* aVertexData
			, CU::GrowingArray<D3D11_INPUT_ELEMENT_DESC*>& someInputElements, Surface& aSurface
			, ModelData* someData);

		

		FBXLoader *myLoader;

		std::unordered_map<std::string, Model*> myModels;
	};
}