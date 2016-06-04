#include "stdafx.h"

#include "Model.h"
#include "ModelProxy.h"

namespace Easy3D
{
	ModelProxy::ModelProxy()
		: myModel(nullptr)
	{
	}


	ModelProxy::~ModelProxy()
	{
	}

	void ModelProxy::Render(Renderer* aRenderer)
	{
		if (IsLoaded() == true)
		{
			myModel->Render(aRenderer);
		}
	}

	const Easy3D::ModelData& ModelProxy::GetData() const
	{
		DL_ASSERT_EXP(IsLoaded() == true, "Model needs to be loaded before you can GetData");
		return myModel->GetData();
	}

}