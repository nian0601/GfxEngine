#include "stdafx.h"
#include "Camera.h"

namespace Frost
{
	Camera::Camera()
	{
		CU::Vector2<float> size = Engine::GetInstance()->GetWindowSize();
		myProjection = CU::Matrix44<float>::CreateProjectionMatrixLH(0.1f, 100.f, size.y / size.x, PI * 0.5f);
	}


	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
		myView = CU::InverseSimple(myOrientation);
	}

	void Camera::Resize(const CU::Vector2<float>& aSize)
	{
		myProjection = CU::Matrix44<float>::CreateProjectionMatrixLH(0.1f, 100.f, aSize.y / aSize.x, PI * 0.5f);
	}
}