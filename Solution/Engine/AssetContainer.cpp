#include "stdafx.h"
#include "AssetContainer.h"
#include "Effect.h"
#include "Instance.h"
#include "Model.h"
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

	Instance* AssetContainer::RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, const CU::String<50>& aEffectPath)
	{
		Effect* effect = GPUContainer::GetInstance()->RequestEffect(aEffectPath);

		myNonDGFXModels.Add(new Model());
		myNonDGFXModels.GetLast()->InitCube(aSize, aColor, effect);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModel = myNonDGFXModels.GetLast();

		Instance* instance = new Instance(*proxy, *effect);
		return instance;
	}

	Instance* AssetContainer::RequestModel(const CU::String<50>& aModelPath, const CU::String<50>& aEffectPath)
	{
		Effect* effect = GPUContainer::GetInstance()->RequestEffect(aEffectPath);

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