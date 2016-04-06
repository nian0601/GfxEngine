Matrix World;
Matrix View;
Matrix Projection;
Matrix ViewProjection;

SamplerState linearSampling
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};


struct VS_INPUT_CUBE3D
{
	float4 Position : POSITION;
	float4 Color : COLOR;
};

struct PS_INPUT_CUBE3D
{
	float4 Position : SV_POSITION;
};

PS_INPUT_CUBE3D VS(VS_INPUT_CUBE3D input)
{
	PS_INPUT_CUBE3D output = (PS_INPUT_CUBE3D)0;

/*
	output.Position = input.Position * float4(Scale, 1);
*/
	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);


	output.Position = input.Position;
	return output;
}

float4 PS(PS_INPUT_CUBE3D input) : SV_Target
{
	return float4(0.f, 1.f, 0.f, 1.f);
	//return Color;
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
