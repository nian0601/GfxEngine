#pragma once

#include <string.h>

struct ID3D11ShaderResourceView;

namespace Frost
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void LoadTexture(const std::string& aPath);

		ID3D11ShaderResourceView* GetShaderView();

	private:
		ID3D11ShaderResourceView* myShaderView;
		std::string myFilePath;
	};

	inline ID3D11ShaderResourceView* Texture::GetShaderView()
	{
		return myShaderView;
	}
}