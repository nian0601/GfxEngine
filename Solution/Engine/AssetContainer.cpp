#include "stdafx.h"
#include "AssetContainer.h"
#include "Effect.h"
#include "Instance.h"
#include "ModelProxy.h"
#include "FBXFactory.h"
#include "Texture.h"

#include "GPUContainer.h"

namespace Easy3D
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

	Instance* AssetContainer::RequestModel(const CU::String<50>& aModelPath, const CU::String<50>& aEffectPath)
	{
		EffectID effect = GPUContainer::GetInstance()->LoadEffect(aEffectPath);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModelData = myModelFactory->LoadModel(aModelPath, effect);

		Instance* instance = new Instance(*proxy, effect);
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