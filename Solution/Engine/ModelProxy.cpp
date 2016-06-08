#include "stdafx.h"

#include "ModelProxy.h"
#include "Renderer.h"

namespace Easy3D
{
	ModelProxy::ModelProxy()
		: myModelData(nullptr)
	{
	}


	ModelProxy::~ModelProxy()
	{
	}

	void ModelProxy::Render(Renderer* aRenderer)
	{
		if (IsLoaded() == true)
		{
			aRenderer->RenderModel(*myModelData, "Render");
		}
	}

	const Easy3D::ModelData& ModelProxy::GetData() const
	{
		DL_ASSERT_EXP(IsLoaded() == true, "Model needs to be loaded before you can GetData");
		return *myModelData;
	}

}