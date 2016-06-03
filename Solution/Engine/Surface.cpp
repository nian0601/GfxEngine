#include "stdafx.h"

#include "GPUContainer.h"
#include <d3dx11effect.h>
#include "Effect.h"
#include "Texture.h"
#include "Surface.h"


namespace Easy3D
{
	Surface::Surface()
		: myResourceViews(5)
		, myShaderResourceNames(5)
		, myShaderVariables(5)
	{
	}


	Surface::~Surface()
	{
	}

	void Surface::AddTexture(const CU::String<50>& aTeturePath, const CU::String<30>& aResourceName)
	{
		Texture* tex = GPUContainer::GetInstance()->RequestTexture(aTeturePath);

		myResourceViews.Add(tex->GetShaderView());
		myShaderResourceNames.Add(aResourceName);
	}

	void Surface::GetShaderResources(Effect* aEffect)
	{
		for each (const CU::String<30>& resourceName in myShaderResourceNames)
		{
			myShaderVariables.Add(aEffect->GetEffect()->GetVariableByName(resourceName.c_str())->AsShaderResource());
		}
	}

	void Surface::Activate()
	{
		for (int i = 0; i < myShaderVariables.Size(); ++i)
		{
			myShaderVariables[i]->SetResource(myResourceViews[i]);
		}
	}

	void Surface::Deactivate()
	{
		for (int i = 0; i < myShaderVariables.Size(); ++i)
		{
			myShaderVariables[i]->SetResource(nullptr);
		}
	}

}