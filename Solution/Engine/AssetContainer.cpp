#include "stdafx.h"
#include "AssetContainer.h"
#include "Effect.h"
#include "Instance.h"
#include "Model.h"
#include "ModelProxy.h"
#include "FBXFactory.h"
#include "Texture.h"

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
		Effect* effect = RequestEffect(aEffectPath);

		myNonDGFXModels.Add(new Model());
		myNonDGFXModels.GetLast()->InitCube(aSize, aColor, effect);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModel = myNonDGFXModels.GetLast();

		Instance* instance = new Instance(*proxy, *effect);
		return instance;
	}

	Instance* AssetContainer::RequestModel(const std::string& aModelPath, const std::string& aEffectPath)
	{
		Effect* effect = RequestEffect(aEffectPath);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModel = myModelFactory->LoadModel(aModelPath, effect);

		Instance* instance = new Instance(*proxy, *effect);
		return instance;
	}

	Effect* AssetContainer::RequestEffect(const std::string& aFilePath)
	{
		if (myEffects.find(aFilePath) == myEffects.end())
		{
			Effect* effect = new Effect();
			effect->Init(aFilePath);

			myEffects[aFilePath] = effect;
		}

		return myEffects[aFilePath];
	}

	Texture* AssetContainer::RequestTexture(const std::string& aFilePath)
	{
		if (myTextures.find(aFilePath) == myTextures.end())
		{
			Texture* newTex = new Texture();
			newTex->LoadTexture(aFilePath);
			myTextures[aFilePath] = newTex;
		}

		return myTextures[aFilePath];
	}

	AssetContainer::AssetContainer()
		: myNonDGFXModels(16)
		, myModelFactory(new FBXFactory())
	{
	}


	AssetContainer::~AssetContainer()
	{
		SAFE_DELETE(myModelFactory);

		for (auto it = myEffects.begin(); it != myEffects.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		myEffects.clear();

		for (auto it = myTextures.begin(); it != myTextures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		myTextures.clear();
	}
}