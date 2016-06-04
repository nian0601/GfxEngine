#pragma once
#include <Matrix.h>

namespace Easy3D
{
	class Camera;
	class Effect;
	class ModelProxy;
	class Renderer;

	class Instance
	{
	public:
		Instance(ModelProxy& aModel, Effect& aEffect);
		~Instance();

		void Render(Renderer* aRenderer, const Camera& aCamera);

		void SetPosition(const CU::Vector3<float>& aPosition);
		CU::Vector3<float> GetPosition() const;

	private:
		void operator=(Instance&) = delete;

		CU::Matrix44<float> myOrientation;
		ModelProxy& myModel;
		Effect& myEffect;
	};
}