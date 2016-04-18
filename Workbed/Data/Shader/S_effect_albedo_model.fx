#include "S_u_variables.fx"

PixelShader_Model VS(VertexShader_Model aInput)
{
	PixelShader_Model output = (PixelShader_Model)0;
	output.Position = mul(aInput.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	
	output.Tex = aInput.Tex;
	
	output.Normal = mul(aInput.Normal, World);
	output.BiNormal = aInput.BiNormal;
	output.Tangent = mul(aInput.Tangent, World);

	output.WorldPosition = mul(aInput.Position, World);
	
	return output;
}

float4 PS(PixelShader_Model aInput) : SV_Target
{
	float3 norm = NormalTexture.Sample(linearSampling, aInput.Tex) * 2 - 1;
	
	aInput.Normal = normalize(aInput.Normal);
	aInput.BiNormal = normalize(aInput.BiNormal);
	aInput.Tangent  = normalize(aInput.Tangent);
	
	float3x3 tangentSpaceMatrix = float3x3(aInput.Tangent, aInput.BiNormal, aInput.Normal);
	norm = normalize(mul(norm, tangentSpaceMatrix));

	float ambient = 0.3f;
	
	float4 AlbedoColor = AlbedoTexture.Sample(linearSampling, aInput.Tex);
	float4 finalColor = AlbedoColor * ambient;
	float4 AmbientOcclusion = AOTexture.Sample(linearSampling, aInput.Tex);

	finalColor *= AmbientOcclusion;
	finalColor.a = 1.f;
	
	return finalColor;
}

technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}