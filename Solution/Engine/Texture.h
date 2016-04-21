#pragma once

#include <string.h>

struct ID3D11DepthStencilView;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;

namespace Frost
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void InitForShader(float aWidth, float aHeight, unsigned int aBindFlag
			, unsigned int aFormat);
		void LoadTexture(const std::string& aPath);

		ID3D11ShaderResourceView* GetShaderView();

	private:
		void CreateShaderViewAndRenderTarget(float aWidth, float aHeight, unsigned int aBindFlag
			, unsigned int aFormat);
		void CreateDepthStencil(float aWidth, float aHeight);

		std::string myFilePath;

		ID3D11Texture2D* myTexture;
		ID3D11ShaderResourceView* myShaderView;
		ID3D11RenderTargetView* myRenderTarget;

		ID3D11Texture2D* myDepthTexture;
		ID3D11ShaderResourceView* myDepthShaderView;
		ID3D11DepthStencilView* myDepthStencil;
	};

	inline ID3D11ShaderResourceView* Texture::GetShaderView()
	{
		return myShaderView;
	}
}