#pragma once
#include "BaseModel.h"
#include <Vector.h>
#include <Matrix.h>

namespace Frost
{
	class Model : public BaseModel
	{
	public:
		Model();
		~Model();

		void InitTriangle(Effect& aEffect);
		void InitCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect& aEffect);

		void Render(Effect& aEffect) override;

	private:
	};
}