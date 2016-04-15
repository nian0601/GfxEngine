#pragma once

namespace Frost
{
	class Camera;
	class Model;
	class Effect;

	class ModelProxy
	{
		friend class AssetSystem;
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