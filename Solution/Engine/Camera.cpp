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

	void Camera::Move(const CU::Vector3<float>& aMoveAmount)
	{
		myOrientation.SetPos(myOrientation.GetPos() + aMoveAmount * myOrientation);
	}

	void Camera::Rotate(const CU::Matrix44<float>& aRotation)
	{
		CU::Vector3<float> pos = myOrientation.GetPos();
		myOrientation.SetPos(CU::Vector3<float>());
		myOrientation = myOrientation * aRotation;
		myOrientation.SetPos(pos);
	}

}