#pragma once

namespace Easy3D
{
	class ModelData;
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
		ModelData* myModelData;
	};

	inline bool ModelProxy::IsLoaded() const
	{
		int DoRealLoadedCheckhere = 5;
		return true;
	}
}