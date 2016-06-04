#include "stdafx.h"

#include "GPUContainer.h"
#include <d3dx11effect.h>
#include "Effect.h"
#include "Texture.h"
#include "Surface.h"


namespace Easy3D
{
	Surface::Surface()
		: myTextures(5)
		, myShaderResourceNames(5)
	{
	}


	Surface::~Surface()
	{
	}

	void Surface::AddTexture(const CU::String<50>& aTeturePath, const CU::String<50>& aResourceName)
	{
		Texture* tex = GPUContainer::GetInstance()->RequestTexture(aTeturePath);

		myTextures.Add(tex);
		myShaderResourceNames.Add(aResourceName);
	}
}