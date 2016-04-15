#include "stdafx.h"

#include "Camera.h"
#include "ModelProxy.h"
#include "Effect.h"
#include "Instance.h"


namespace Frost
{
	Instance::Instance(ModelProxy& aModel, Effect& aEffect)
		: myModel(aModel)
		, myEffect(aEffect)
	{
	}


	Instance::~Instance()
	{
	}

	void Instance::Render(const Camera& aCamera)
	{
		myEffect.SetViewMatrix(aCamera.GetView());
		myEffect.SetProjectionMatrix(aCamera.GetProjection());
		myEffect.SetWorldMatrix(myOrientation);

		myModel.Render(myEffect);
	}

	void Instance::SetPosition(const CU::Vector3<float>& aPosition)
	{
		myOrientation.SetPos(aPosition);
	}

}