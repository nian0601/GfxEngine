#pragma once

struct ID3DX11Effect;
struct ID3DX11EffectTechnique;
struct ID3DX11EffectMatrixVariable;
struct ID3DX11EffectShaderResourceVariable;
struct ID3DX11EffectVectorVariable;
struct ID3DX11EffectScalarVariable;

namespace Frost
{
	class Texture;

	class Effect
	{
	public:
		Effect();
		~Effect();

		void Init(const std::string& aFilePath);

		ID3DX11Effect* GetEffect() const;
		ID3DX11EffectTechnique* GetTechnique(const std::string& aTechniqueName) const;


		void SetWorldMatrix(const CU::Matrix44<float>& aWorldMatrix);
		void SetViewMatrix(const CU::Matrix44<float>& aViewMatrix);
		void SetProjectionMatrix(const CU::Matrix44<float>& aProjectionMatrix);
		void SetViewProjectionMatrix(const CU::Matrix44<float>& aMatrix);

		void SetCubemap(Texture* aTexture);

		void SetCameraPosition(const CU::Vector3<float>& aVector);

		void SetMetalness(float aValue);
		void SetRoughness(float aValue);

	private:
		void LoadMatrix(ID3DX11EffectMatrixVariable*& aMatrix, const std::string& aVariableName, bool aForceFind = true);
		void LoadShaderResource(ID3DX11EffectShaderResourceVariable*& aResource, const std::string& aVariableName, bool aForceFind = true);
		void LoadVector(ID3DX11EffectVectorVariable*& aVector, const std::string& aVariableName, bool aForceFind = true);
		void LoadScalar(ID3DX11EffectScalarVariable*& aScalar, const std::string& aVariableName, bool aForceFind = true);

		ID3DX11Effect* myEffect;

		ID3DX11EffectMatrixVariable* myProjectionMatrix;
		ID3DX11EffectMatrixVariable* myViewMatrix;
		ID3DX11EffectMatrixVariable* myWorldMatrix;
		ID3DX11EffectMatrixVariable* myViewProjectionMatrix;

		ID3DX11EffectShaderResourceVariable* myCubemap;

		ID3DX11EffectVectorVariable* myCameraPosition;

		ID3DX11EffectScalarVariable* myMetalness;
		ID3DX11EffectScalarVariable* myRoughness;

		std::string myFileName;
		std::string myFilePath;
	};
}