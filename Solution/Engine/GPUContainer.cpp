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

	Easy3D::Effect* GPUContainer::RequestEffect(const CU::String<50>& aFilePath)
	{
		if (myEffects.KeyExists(aFilePath) == false)
		{
			Effect* effect = new Effect();
			effect->Init(aFilePath);

			myEffects[aFilePath] = effect;
		}

		return myEffects[aFilePath];
	}

	Easy3D::Texture* GPUContainer::RequestTexture(const CU::String<50>& aFilePath)
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
		/*
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
		*/
	}
}