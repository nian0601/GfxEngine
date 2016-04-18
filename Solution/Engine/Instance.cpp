#include "stdafx.h"

#include "Camera.h"
#include "ModelProxy.h"
#include "Effect.h"
#include "Instance.h"

#include "TextureContainer.h"

namespace Frost
{
	Instance::Instance(ModelProxy& aModel, Effect& aEffect)
		: myModel(aModel)
		, myEffect(aEffect)
	{
		myCubemap = TextureContainer::GetInstance()->Get("Data/Texture/church_cubemap.dds");
	}


	Instance::~Instance()
	{
	}

	void Instance::Render(const Camera& aCamera)
	{
		myEffect.SetViewMatrix(aCamera.GetView());
		myEffect.SetProjectionMatrix(aCamera.GetProjection());
		myEffect.SetWorldMatrix(myOrientation);

		myEffect.SetCubemap(myCubemap);

		myEffect.SetCameraPosition(aCamera.GetPosition());

		myModel.Render(myEffect);
	}

	void Instance::SetPosition(const CU::Vector3<float>& aPosition)
	{
		myOrientation.SetPos(aPosition);
	}

}