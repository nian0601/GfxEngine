#include "stdafx.h"

#include "AssetContainer.h"
#include "Camera.h"
#include "Effect.h"
#include "Instance.h"
#include "Renderer.h"

namespace Easy3D
{
	Instance::Instance(ModelID aModelID, EffectID aEffect)
		: myModelID(aModelID)
		, myEffect(aEffect)
	{
	}


	Instance::~Instance()
	{
	}

	void Instance::Render(Renderer* aRenderer, const Camera& aCamera)
	{
		aRenderer->SetEffect(myEffect);
		aRenderer->SetMatrix("ViewProjection", aCamera.GetViewProjection());
		aRenderer->SetMatrix("World", myOrientation);
		aRenderer->SetVector("CameraPosition", aCamera.GetPosition());

		aRenderer->RenderModel(myModelID);
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