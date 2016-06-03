#pragma once

#include <Matrix.h>
#include <Vector.h>

namespace Easy3D
{
	struct PointLightData
	{
		CU::Vector3<float> myPosition;
		CU::Vector4<float> myColor;
		float myRange;
	};

	class Instance;
	class PointLight
	{
	public:
		PointLight(const CU::Vector3<float>& aPosition, const CU::Vector4<float>& aColor, float aRange);
		~PointLight();

		const PointLightData& GetData() const;

	private:
		Instance* myLightMesh;
		PointLightData myData;
	};

	inline const PointLightData& PointLight::GetData() const
	{
		return myData;
	}
}