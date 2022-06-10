cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;

	float4 camPos;
};

cbuffer LightBuffer : register(b1)
{
	float3 lightPosition;
	float3 direction;
	float4 ambient;
	float4 diffuse;

	matrix lightView;
	matrix lightProj;

	float range;
	float innerCone;
	float outerCone;
};

struct VS_IN
{
	float4 position : POSITION;
};

struct VS_OUT
{
	float4 position		: SV_POSITION;
	float4 depthPosition : TEXTURE0;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;

	input.position.w = 1.0f;

	output.position = mul(input.position, world);
	output.position = mul(output.position, lightView);
	output.position = mul(output.position, lightProj);

	output.depthPosition = output.position;

	return output;
}