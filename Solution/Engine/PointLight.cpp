#include "stdafx.h"

#include "Instance.h"
#include "PointLight.h"


namespace Easy3D
{
	PointLight::PointLight(const CU::Vector3<float>& aPosition, const CU::Vector4<float>& aColor, float aRange)
	{
		myData.myPosition = aPosition;
		myData.myColor = aColor;
		myData.myRange = aRange;
	}


	PointLight::~PointLight()
	{
	}
}