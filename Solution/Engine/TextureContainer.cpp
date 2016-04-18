#include "stdafx.h"

#include "Texture.h"
#include "TextureContainer.h"


namespace Frost
{
	TextureContainer* TextureContainer::myInstance = nullptr;

	TextureContainer* TextureContainer::GetInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new TextureContainer();
		}

		return myInstance;
	}

	void TextureContainer::Destory()
	{
		SAFE_DELETE(myInstance);
	}

	Texture* TextureContainer::Get(const std::string& aFilePath)
	{
		if (myTextures.find(aFilePath) == myTextures.end())
		{
			Texture* newTex = new Texture();
			newTex->LoadTexture(aFilePath);
			myTextures[aFilePath] = newTex;
		}

		return myTextures[aFilePath];
	}

	TextureContainer::TextureContainer()
	{
	}


	TextureContainer::~TextureContainer()
	{
		for (auto it = myTextures.begin(); it != myTextures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		myTextures.clear();
	}
}