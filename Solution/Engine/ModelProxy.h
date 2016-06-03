#pragma once

namespace Easy3D
{
	class Camera;
	class Model;
	class Effect;

	class ModelProxy
	{
		friend class AssetContainer;
	public:
		ModelProxy();
		~ModelProxy();

		void Render(Effect& aEffect);

		bool IsLoaded() const;

	private:
		Model* myModel;
	};

	inline bool ModelProxy::IsLoaded() const
	{
		return myModel != nullptr;
	}
}