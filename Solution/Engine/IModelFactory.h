#pragma once
#include <CUString.h>

namespace Easy3D
{
	class Effect;
	class Model;

	class IModelFactory
	{
	public:
		virtual ~IModelFactory(){};

		virtual Model* LoadModel(const CU::String<50>& aFilePath, Effect* aEffect) = 0;

	protected:
		IModelFactory(){};
	};
}