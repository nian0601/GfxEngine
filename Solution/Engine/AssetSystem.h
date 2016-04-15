#pragma once
#include <GrowingArray.h>
#include <Vector.h>

namespace std
{
	class thread;
}

namespace Frost
{
	class Instance;
	class Effect;
	class Model;

	class AssetSystem
	{
	public:
		static AssetSystem* GetInstance();
		static void Destroy();


		Instance* RequestCube(const CU::Vector3<float>& aSize, const CU::Vector4<float>& aColor, Effect& aEffect);

	private:
		AssetSystem();
		~AssetSystem();

		void Run();

		CU::GrowingArray<Model*> myNonDGFXModels;

		static AssetSystem* myInstance;
	};
}