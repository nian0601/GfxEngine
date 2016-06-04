#include "stdafx.h"

#include "AssetContainer.h"
#include "Camera.h"
#include "ModelProxy.h"
#include "Effect.h"
#include "Instance.h"
#include "Renderer.h"

namespace Easy3D
{
	Instance::Instance(ModelProxy& aModel, Effect& aEffect)
		: myModel(aModel)
		, myEffect(aEffect)
	{
	}


	Instance::~Instance()
	{
	}

	void Instance::Render(Renderer* aRenderer, const Camera& aCamera)
	{
		if (myModel.IsLoaded() == true)
		{
			aRenderer->SetEffect(&myEffect);
			aRenderer->SetMatrix("View", aCamera.GetView());
			aRenderer->SetMatrix("Projection", aCamera.GetProjection());
			aRenderer->SetMatrix("World", myOrientation);
			aRenderer->SetVector("CameraPosition", aCamera.GetPosition());

			myModel.Render(aRenderer);
		}
	}

	void Instance::SetPosition(const CU::Vector3<float>& aPosition)
	{
		myOrientation.SetPos(aPosition);
	}

	CU::Vector3<float> Instance::GetPosition() const
	{
		return myOrientation.GetPos();
	}

}