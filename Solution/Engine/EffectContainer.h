#pragma once

#include <string.h>
#include <unordered_map>

namespace Frost
{
	class Effect;

	class EffectContainer
	{
	public:
		static EffectContainer* GetInstance();
		static void Destory();

		Effect* Get(const std::string& aFilePath);

	private:
		EffectContainer();
		~EffectContainer();

		std::unordered_map<std::string, Effect*> myEffects;
		static EffectContainer* myInstance;
	};
}