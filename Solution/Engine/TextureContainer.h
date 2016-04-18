#pragma once

#include <string.h>
#include <unordered_map>

namespace Frost
{
	class Texture;

	class TextureContainer
	{
	public:
		static TextureContainer* GetInstance();
		static void Destory();

		Texture* Get(const std::string& aFilePath);

	private:
		TextureContainer();
		~TextureContainer();

		std::unordered_map<std::string, Texture*> myTextures;
		static TextureContainer* myInstance;
	};
}