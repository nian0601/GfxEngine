#include "stdafx.h"
#include "AssetContainer.h"
#include "Effect.h"
#include "Instance.h"
#include "ModelProxy.h"
#include "FBXFactory.h"
#include "Texture.h"

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
		EffectID effect = LoadEffect(aEffectPath);

		ModelProxy* proxy = new ModelProxy();
		proxy->myModelData = myModelFactory->LoadModel(aModelPath, effect);

		Instance* instance = new Instance(*proxy, effect);
		return instance;
	}

	EffectID AssetContainer::LoadEffect(const CU::String<50>& aFilePath)
	{
		if (myEffectsID.KeyExists(aFilePath) == false)
		{
			Effect* effect = new Effect();
			effect->Init(aFilePath);

			myEffects[myNextEffectID] = effect;
			myEffectsID[aFilePath] = myNextEffectID;
			++myNextEffectID;
		}

		return myEffectsID[aFilePath];
	}

	Effect* AssetContainer::GetEffect(EffectID aID)
	{
		if (myEffects.KeyExists(aID) == true)
		{
			return myEffects[aID];
		}

		DL_ASSERT("Tried to Get an Invalid effect");
		return nullptr;
	}

	Texture* AssetContainer::RequestTexture(const CU::String<50>& aFilePath)
	{
		if (myTextures.KeyExists(aFilePath) == false)
		{
			Texture* newTex = new Texture();
			newTex->LoadTexture(aFilePath);
			myTextures[aFilePath] = newTex;
		}

		return myTextures[aFilePath];
	}

	AssetContainer::AssetContainer()
		: myModelFactory(new FBXFactory())
	{
	}


	AssetContainer::~AssetContainer()
	{
		SAFE_DELETE(myModelFactory);

		for (auto it = myEffects.Begin(); it != myEffects.End(); it = myEffects.Next(it))
		{
			SAFE_DELETE(it.Second());
		}
		myEffects.Clear();

		for (auto it = myTextures.Begin(); it != myTextures.End(); it = myTextures.Next(it))
		{
			SAFE_DELETE(it.Second());
		}
		myTextures.Clear();
	}
}