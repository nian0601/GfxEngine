#pragma once
#include <Matrix.h>

namespace Frost
{
	class Camera;
	class Effect;
	class ModelProxy;
	class Texture;

	class Instance
	{
	public:
		Instance(ModelProxy& aModel, Effect& aEffect);
		~Instance();

		void Render(const Camera& aCamera);

		void SetPosition(const CU::Vector3<float>& aPosition);

	private:
		void operator=(Instance&) = delete;

		CU::Matrix44<float> myOrientation;
		ModelProxy& myModel;
		Effect& myEffect;
		Texture* myCubemap;
	};
}