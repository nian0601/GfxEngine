#include "stdafx.h"
#include "AssetSystem.h"
#include "Instance.h"
#include "Model.h"
#include "ModelProxy.h"

namespace Frost
{
	AssetSystem* AssetSystem::myInstance = nullptr;
	AssetSystem* AssetSystem::GetInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new AssetSystem();
		}

		return myInstance;
	}

	void AssetSystem::Destroy()
	{
		SAFE_DELETE(myInstance);
	}

	Instance* AssetSystem::RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect& aEffect)
	{
		myNonDGFXModels.Add(new Model());
		myNonDGFXModels.GetLast()->InitCube(aSize, aColor, aEffect);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModel = myNonDGFXModels.GetLast();

		Instance* instance = new Instance(*proxy, aEffect);
		return instance;
	}

	AssetSystem::AssetSystem()
		: myNonDGFXModels(16)
	{
	}


	AssetSystem::~AssetSystem()
	{
	}
}