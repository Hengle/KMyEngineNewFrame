cbuffer MatrixBuffer
{
	float4x4 wvp;
};

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);


SamplerState SampleTypePoint : register(s0);

cbuffer LightBuffer
{
    float3 lightDirection;
	float padding;
};

struct VertexInputType
{
    float3 position : POSITION;
    float4 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;  

    output.position = mul(float4(input.position,1.0f), wvp);

    
    output.tex = input.tex.xy;
    
	return output;
}


float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
	float4 colors;
	//float4 normals;
	//float3 lightDir;
	//float lightIntensity;
	//float4 outputColor;


	colors = colorTexture.Sample(SampleTypePoint, input.tex);

	//normals = normalTexture.Sample(SampleTypePoint, input.tex);
	//
 //   lightDir = -lightDirection;

 //   lightIntensity = saturate(dot(normals.xyz, lightDir));

 //   outputColor = saturate(colors * lightIntensity);

    return colors;

}
