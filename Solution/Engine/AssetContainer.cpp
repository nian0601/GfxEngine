#include "stdafx.h"
#include "AssetContainer.h"
#include "EffectContainer.h"
#include "Instance.h"
#include "Model.h"
#include "ModelProxy.h"
#include "FBXFactory.h"

namespace Frost
{
	AssetContainer* AssetContainer::myInstance = nullptr;
	AssetContainer* AssetContainer::GetInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new AssetContainer();
		}

		return myInstance;
	}

	void AssetContainer::Destroy()
	{
		SAFE_DELETE(myInstance);
	}

	Instance* AssetContainer::RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, const std::string& aEffectPath)
	{
		Effect* effect = EffectContainer::GetInstance()->Get(aEffectPath);

		myNonDGFXModels.Add(new Model());
		myNonDGFXModels.GetLast()->InitCube(aSize, aColor, effect);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModel = myNonDGFXModels.GetLast();

		Instance* instance = new Instance(*proxy, *effect);
		return instance;
	}

	Instance* AssetContainer::RequestModel(const std::string& aModelPath, const std::string& aEffectPath)
	{
		Effect* effect = EffectContainer::GetInstance()->Get(aEffectPath);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModel = myModelFactory->LoadModel(aModelPath, effect);

		Instance* instance = new Instance(*proxy, *effect);
		return instance;
	}

	AssetContainer::AssetContainer()
		: myNonDGFXModels(16)
		, myModelFactory(new FBXFactory())
	{
	}


	AssetContainer::~AssetContainer()
	{
		SAFE_DELETE(myModelFactory);
	}
}