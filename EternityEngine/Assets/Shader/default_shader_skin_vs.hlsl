Texture2D textureDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix proj;
	float4 camPos;
	matrix boneMatrix[512];
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
	float4 position : POSITION0;
	float3 normal	: NORMAL0;
	float4 color	: COLOR0;
	float2 tex		: TEXCOORD0;
	int4 index		: BLENDINDICES;
	float3 weight	: BLENDWEIGHT;
};

struct VS_OUT
{
	float4 position		: SV_POSITION;
	float3 color		: COLOR0;
	float3 normal		: NORMAL;
	float2 tex			: TEXCOORD0;
	float4 lightViewPos : TEXCOORD1;
	float3 lightPos		: TEXCOORD2;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;
	float4 position = (float4)0;
	float blendWeights[3] = (float[3])input.weight;
	matrix worldComb = (matrix)0;

	for (int i = 0; i < 3; ++i)
	{
		worldComb += boneMatrix[input.index[i]] * blendWeights[i];
	}
	worldComb += boneMatrix[input.index[3]] * (1.0f - blendWeights[0] - blendWeights[1] - blendWeights[2]);

	output.position = mul(input.position, worldComb);
	output.position = mul(output.position, view);
	output.position = mul(output.position, proj);

	output.lightViewPos = mul(input.position, worldComb);
	output.lightViewPos = mul(output.lightViewPos, lightView);
	output.lightViewPos = mul(output.lightViewPos, lightProj);

	output.color = input.color;

	output.tex = input.tex;

	output.normal = mul(input.normal, worldComb);
	output.normal = normalize(output.normal);

	position = mul(input.position, world);

	output.lightPos = lightPosition.xyz - position.xyz;
	output.lightPos = normalize(output.lightPos);

	return output;
}