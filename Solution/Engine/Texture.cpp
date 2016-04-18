#include "stdafx.h"

#include <D3DX11tex.h>
#include "Texture.h"


namespace Frost
{
	Texture::Texture()
		: myShaderView(nullptr)
	{
	}


	Texture::~Texture()
	{
		SAFE_RELEASE(myShaderView);
	}

	void Texture::LoadTexture(const std::string& aPath)
	{
		myFilePath = aPath;

		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(Engine::GetInstance()->GetDevice()
			, myFilePath.c_str(), NULL, NULL, &myShaderView, NULL);
		

		if (FAILED(hr) != S_OK)
		{
			DL_MESSAGE_BOX(CU::Concatenate("Failed to load: %s,\ntrying to use MissingTexture-texture.", myFilePath.c_str()).c_str()
				, "Failed to load texture", MB_ICONWARNING);

			myFilePath = "Data/Resource/Texture/T_missing_texture.dds";
			hr = D3DX11CreateShaderResourceViewFromFile(Engine::GetInstance()->GetDevice()
				, myFilePath.c_str(), NULL, NULL, &myShaderView, NULL);

			
			if (FAILED(hr) != S_OK)
			{
				DL_ASSERT("[Texture]: Failed to load MissingTexture-texture: Data/Resource/Texture/T_missing_texture.dds");
			}
		}
	}
}