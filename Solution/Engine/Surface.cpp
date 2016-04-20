#include "stdafx.h"

#include "AssetContainer.h"
#include <d3dx11effect.h>
#include "Effect.h"
#include "Texture.h"
#include "Surface.h"


namespace Frost
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

	void Surface::AddTexture(const std::string& aTeturePath, const std::string& aResourceName)
	{
		Texture* tex = AssetContainer::GetInstance()->RequestTexture(aTeturePath);

		myResourceViews.Add(tex->GetShaderView());
		myShaderResourceNames.Add(aResourceName);
	}

	void Surface::GetShaderResources(Effect* aEffect)
	{
		for each (const std::string& resourceName in myShaderResourceNames)
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