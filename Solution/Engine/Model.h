#pragma once
#include "BaseModel.h"
#include <Vector.h>
#include <Matrix.h>

class Model : public BaseModel
{
public:
	Model();
	~Model();

	void InitTriangle(Effect* aEffect);
	void InitCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect* aEffect);

	void Render() override;

private:
	CU::Matrix44<float> myOrientation;
	CU::Matrix44<float> myView;
	CU::Matrix44<float> myProjection;
};

