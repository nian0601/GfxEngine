#include "stdafx.h"
#include "AssetContainer.h"
#include "Effect.h"
#include "Instance.h"
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

	Instance* AssetContainer::LoadModel(const CU::String<64>& aModelPath, const CU::String<64>& aEffectPath)
	{
		EffectID effect = LoadEffect(aEffectPath);

		if (myModelID.KeyExists(aModelPath) == false)
		{
			ModelData* modelData = myModelFactory->LoadModel(aModelPath, effect);

			myModels[myNextModelID] = modelData;
			myModelID[aModelPath] = myNextModelID;
			++myNextModelID;
		}

		return new Instance(myModelID[aModelPath], effect);
	}

	Easy3D::ModelData* AssetContainer::GetModel(ModelID aID)
	{
		if (myModels.KeyExists(aID) == true)
		{
			return myModels[aID];
		}

		DL_ASSERT("Tried to Get an Invalid model");
		return nullptr;
	}

	EffectID AssetContainer::LoadEffect(const CU::String<64>& aFilePath)
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

	Texture* AssetContainer::RequestTexture(const CU::String<64>& aFilePath)
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