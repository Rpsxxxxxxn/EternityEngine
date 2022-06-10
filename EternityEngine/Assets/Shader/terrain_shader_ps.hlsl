static const float BIAS = 0.0001f;

Texture2D grassTexture : register(t0);
Texture2D slopeTexture : register(t1);
Texture2D rockTexture  : register(t2);

SamplerState samLinear : register(s0);
SamplerState samWrap : register(s1);

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

struct PS_IN
{
	float4 position		: SV_POSITION;
	float3 color		: COLOR0;
	float3 normal		: NORMAL;
	float2 tex			: TEXCOORD0;
	float4 lightViewPos : TEXCOORD1;
	float3 lightPos		: TEXCOORD2;
	float fogFactor : FOG;
};

float4 main(PS_IN input) : SV_Target0
{
	float4 textureColor = 1.0f;

	float color = 1.0f;

	float blendAmount = 1.0f;

	float4 grassColor = grassTexture.Sample(samWrap, input.tex);

	float4 slopeColor = slopeTexture.Sample(samWrap, input.tex);

	float4 rockColor = rockTexture.Sample(samWrap, input.tex);

	float slope = 1.0f - input.normal.y;

	if (slope < 0.4)
	{
		blendAmount = slope / 0.4f;
		textureColor = lerp(grassColor, slopeColor, blendAmount);
	}

	if ((slope < 0.5) && (slope >= 0.4f))
	{
		blendAmount = (slope - 0.4f) * (1.0f / (0.6f - 0.4f));
		textureColor = lerp(slopeColor, rockColor, blendAmount);
	}

	if (slope >= 0.5)
	{
		textureColor = rockColor;
	}

	float3 eyeVector = normalize(camPos.xyz - input.position.xyz);

	float3 halfVector = normalize(direction + normalize(lightPosition.xyz));

	float specular = pow(max(0.0f, dot(input.normal, halfVector)), 20.0f) * 0.95f;

	float4 fogColor = float4(0.5f, 0.5f, 0.5f, 1.0f);

	float4 finalColor = input.fogFactor * (color * (textureColor + (1.0f - input.fogFactor) * fogColor) + specular);

	return saturate(finalColor);
}