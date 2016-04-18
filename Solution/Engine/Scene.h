#pragma once
#include <GrowingArray.h>

namespace Frost
{
	class Camera;
	class Instance;
	
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Render();

		void SetCamera(Camera& aCamera);

		void AddInstance(Instance* aInstance);
		void RemoveInstance(Instance* aInstance);

	private:
		CU::GrowingArray<Instance*> myInstances;
		Camera* myCamera;
	};
}