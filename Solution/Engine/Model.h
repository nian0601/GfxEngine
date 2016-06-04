#pragma once
#include "BaseModel.h"
#include <Vector.h>
#include <Matrix.h>
#include <GrowingArray.h>

namespace Easy3D
{
	class Surface;
	class Renderer;

	class Model : public BaseModel
	{
		friend class FBXFactory;
	public:
		Model();
		~Model();

		void AddChild(Model* aModel);

		void Init(Effect* aEffect);
		void InitCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect* aEffect);

		void Render(Renderer* aRenderer);

	private:
		CU::GrowingArray<Model*> myChildren;
		CU::GrowingArray<CU::Matrix44<float>> myChildTransforms;
		CU::Matrix44<float> myOrientation;

		CU::GrowingArray<Surface*> mySurfaces;
	};
}