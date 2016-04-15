#pragma once

#include <Matrix.h>

namespace Frost
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update();
		void Resize(const CU::Vector2<float>& aSize);


		const CU::Matrix44<float>& GetView() const;
		const CU::Matrix44<float>& GetProjection() const;

	private:
		CU::Matrix44<float> myProjection;
		CU::Matrix44<float> myView;

		CU::Matrix44<float> myOrientation;
	};

	inline const CU::Matrix44<float>& Camera::GetView() const
	{
		return myView;
	}

	inline const CU::Matrix44<float>& Camera::GetProjection() const
	{
		return myProjection;
	}
}

