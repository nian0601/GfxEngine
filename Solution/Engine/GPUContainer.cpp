#include "stdafx.h"

#include "Effect.h"
#include "GPUContainer.h"
#include "Texture.h"


namespace Easy3D
{
	GPUContainer* GPUContainer::myInstance = nullptr;
	GPUContainer* GPUContainer::GetInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new GPUContainer();
		}

		return myInstance;
	}

	void GPUContainer::Destroy()
	{
		SAFE_DELETE(myInstance);
	}

	EffectID GPUContainer::LoadEffect(const CU::String<50>& aFilePath)
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

	Effect* GPUContainer::GetEffect(EffectID aID)
	{
		if (myEffects.KeyExists(aID) == true)
		{
			return myEffects[aID];
		}

		DL_ASSERT("Tried to Get an Invalid effect");
		return nullptr;
	}

	Texture* GPUContainer::RequestTexture(const CU::String<50>& aFilePath)
	{
		if (myTextures.KeyExists(aFilePath) == false)
		{
			Texture* newTex = new Texture();
			newTex->LoadTexture(aFilePath);
			myTextures[aFilePath] = newTex;
		}

		return myTextures[aFilePath];
	}

	GPUContainer::GPUContainer()
	{
	}


	GPUContainer::~GPUContainer()
	{
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