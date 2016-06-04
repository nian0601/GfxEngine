#pragma once
#include <CUString.h>
#include "EngineTypes.h"

namespace Easy3D
{
	class Effect;
	class Model;

	class IModelFactory
	{
	public:
		virtual ~IModelFactory(){};

		virtual Model* LoadModel(const CU::String<50>& aFilePath, EffectID aEffect) = 0;

	protected:
		IModelFactory(){};
	};
}