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

	void ModelProxy::Render(Effect& aEffect)
	{
		if (IsLoaded())
		{
			myModel->Render(aEffect);
		}
	}
}