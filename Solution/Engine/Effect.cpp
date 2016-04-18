#include "stdafx.h"

#include <d3dx11effect.h>
#include <D3D10effect.h>
#include <D3DX11async.h>
#include <D3Dcompiler.h>
#include "Effect.h"
#include "Texture.h"

namespace Frost
{
	Effect::Effect()
		: myEffect(nullptr)
		, myWorldMatrix(nullptr)
		, myViewMatrix(nullptr)
		, myProjectionMatrix(nullptr)
		, myViewProjectionMatrix(nullptr)
		, myCubemap(nullptr)
		, myCameraPosition(nullptr)
		, myFileName("NOT INITIALIZED")
	{
	}

	Effect::~Effect()
	{
		SAFE_RELEASE(myEffect);
	}

	void Effect::Init(const std::string& aFilePath)
	{
		myFileName = CU::GetFileNameFromFilePath(aFilePath);
		myFilePath = aFilePath;

		unsigned int shaderFlags = 0;
#ifdef _DEBUG
		shaderFlags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

		ID3D10Blob* compiledShader = nullptr;
		ID3D10Blob* compilerMsg = nullptr;

		HRESULT result = D3DX11CompileFromFile(myFilePath.c_str(), 0, 0, 0, "fx_5_0", shaderFlags, 0, 0, &compiledShader, &compilerMsg, 0);

		if (FAILED(result))
		{
			std::string errorMessage = "";

			if (compilerMsg != nullptr)
			{
				DL_MESSAGE_BOX((char*)compilerMsg->GetBufferPointer(), "Effect Error", MB_ICONWARNING);

				errorMessage = "[Effect]: Failed to compile";
			}
			else
			{
				errorMessage = "[Effect]: Could not find the effect " + myFileName;
			}

			DL_ASSERT(errorMessage.c_str());
		}

		if (compilerMsg)
		{
			SAFE_RELEASE(compilerMsg);
		}

		result = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, Engine::GetInstance()->GetDevice(), &myEffect);
		DL_ASSERT_EXP(SUCCEEDED(result) == TRUE, "Failed to Create shader");

		if (compiledShader)
		{
			SAFE_RELEASE(compiledShader);
		}

		LoadMatrix(myWorldMatrix, "World");
		LoadMatrix(myViewMatrix, "View");
		LoadMatrix(myProjectionMatrix, "Projection");
		LoadMatrix(myViewProjectionMatrix, "ViewProjection");

		LoadShaderResource(myCubemap, "Cubemap", false);

		LoadVector(myCameraPosition, "CameraPosition");
	}

	ID3DX11Effect* Effect::GetEffect() const
	{
		return myEffect;
	}

	ID3DX11EffectTechnique* Effect::GetTechnique(const std::string& aTechniqueName) const
	{
		return myEffect->GetTechniqueByName(aTechniqueName.c_str());
	}

	void Effect::SetWorldMatrix(const CU::Matrix44<float>& aWorldMatrix)
	{
		myWorldMatrix->SetMatrix(&aWorldMatrix.myMatrix[0]);
	}

	void Effect::SetViewMatrix(const CU::Matrix44<float>& aViewMatrix)
	{
		myViewMatrix->SetMatrix(&aViewMatrix.myMatrix[0]);
	}

	void Effect::SetProjectionMatrix(const CU::Matrix44<float>& aProjectionMatrix)
	{
		myProjectionMatrix->SetMatrix(&aProjectionMatrix.myMatrix[0]);
	}

	void Effect::SetViewProjectionMatrix(const CU::Matrix44<float>& aMatrix)
	{
		myViewProjectionMatrix->SetMatrix(&aMatrix.myMatrix[0]);
	}


	void Effect::SetCubemap(Texture* aTexture)
	{
		if (myCubemap)
		{
			myCubemap->SetResource(aTexture->GetShaderView());
		}
	}

	void Effect::SetCameraPosition(const CU::Vector3<float>& aVector)
	{
		myCameraPosition->SetFloatVector(&aVector.x);
	}

	void Effect::LoadMatrix(ID3DX11EffectMatrixVariable*& aMatrix, const std::string& aVariableName, bool aForceFind)
	{
		aMatrix = myEffect->GetVariableByName(aVariableName.c_str())->AsMatrix();
		if (aMatrix->IsValid() == false)
		{
			aMatrix = nullptr;
			if (aForceFind == true)
			{
				DL_ASSERT(CU::Concatenate("Shader: Failed to find variable: %s, in file: %s", aVariableName.c_str(), myFileName.c_str()));
			}
		}
	}

	void Effect::LoadShaderResource(ID3DX11EffectShaderResourceVariable*& aResource, const std::string& aVariableName, bool aForceFind)
	{
		aResource = myEffect->GetVariableByName(aVariableName.c_str())->AsShaderResource();
		if (aResource->IsValid() == false)
		{
			aResource = nullptr;
			if (aForceFind == true)
			{
				DL_ASSERT(CU::Concatenate("Shader: Failed to find variable: %s, in file: %s", aVariableName.c_str(), myFileName.c_str()));
			}
		}
	}

	void Effect::LoadVector(ID3DX11EffectVectorVariable*& aVector, const std::string& aVariableName, bool aForceFind /*= true*/)
	{
		aVector = myEffect->GetVariableByName(aVariableName.c_str())->AsVector();
		if (aVector->IsValid() == false)
		{
			aVector = nullptr;
			if (aForceFind == true)
			{
				DL_ASSERT(CU::Concatenate("Shader: Failed to find variable: %s, in file: %s", aVariableName.c_str(), myFileName.c_str()));
			}
		}
	}

}