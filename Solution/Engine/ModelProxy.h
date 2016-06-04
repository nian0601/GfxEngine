#pragma once

namespace Easy3D
{
	struct ModelData;

	class Camera;
	class Model;
	class Effect;
	class Renderer;

	class ModelProxy
	{
		friend class AssetContainer;
	public:
		ModelProxy();
		~ModelProxy();

		void Render(Renderer* aRenderer);

		bool IsLoaded() const;

		const ModelData& GetData() const;

	private:
		Model* myModel;
	};

	inline bool ModelProxy::IsLoaded() const
	{
		return myModel != nullptr;
	}
}