#pragma once
#include <GrowingArray.h>

namespace Easy3D
{
	class Camera;
	class Instance;
	class Renderer;
	
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Render(Renderer* aRenderer);

		void SetCamera(Camera& aCamera);

		void AddInstance(Instance* aInstance);
		void RemoveInstance(Instance* aInstance);

	private:
		CU::GrowingArray<Instance*> myInstances;
		Camera* myCamera;
	};
}