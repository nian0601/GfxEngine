#include "stdafx.h"

#include "Effect.h"
#include "EffectContainer.h"


namespace Frost
{
	EffectContainer* EffectContainer::myInstance = nullptr;

	EffectContainer* EffectContainer::GetInstance()
	{
		if (myInstance == nullptr)
		{
			myInstance = new EffectContainer();
		}

		return myInstance;
	}

	void EffectContainer::Destory()
	{
		SAFE_DELETE(myInstance);
	}

	Effect* EffectContainer::Get(const std::string& aFilePath)
	{
		if (myEffects.find(aFilePath) == myEffects.end())
		{
			Effect* effect = new Effect();
			effect->Init(aFilePath);

			myEffects[aFilePath] = effect;
		}

		return myEffects[aFilePath];
	}

	EffectContainer::EffectContainer()
	{
	}


	EffectContainer::~EffectContainer()
	{
		for (auto it = myEffects.begin(); it != myEffects.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		myEffects.clear();
	}
}