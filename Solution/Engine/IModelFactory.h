#pragma once
#include <string>

namespace Frost
{
	class Effect;
	class Model;

	class IModelFactory
	{
	public:
		virtual ~IModelFactory(){};

		virtual Model* LoadModel(const std::string& aFilePath, Effect* aEffect) = 0;

	protected:
		IModelFactory(){};
	};
}