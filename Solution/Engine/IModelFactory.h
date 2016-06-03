#pragma once
#include <string>

namespace Easy3D
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