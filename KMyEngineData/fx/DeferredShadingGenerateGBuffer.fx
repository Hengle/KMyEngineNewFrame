cbuffer MatrixBuffer
{
	float4x4 gWorldInvTranspose;
	float4x4 wvp;
};

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;

	float2 depth : TEXCOORD1;
};

struct PixelOutputType
{
    float4 color : SV_Target0;
    float4 normal : SV_Target1;
	float4 specular: SV_Target2;
	float4 depth: SV_Target3;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType DeferredVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    
    input.position.w = 1.0f;
    output.position = mul(input.position, wvp);
    
    output.tex = input.tex;    
    output.normal = mul(input.normal, (float3x3)gWorldInvTranspose);	
    output.normal = normalize(output.normal);
	output.depth = output.position.zw;

	return output;
}

float3 float_to_color( float f)
{
	float3 color;
	f *= 256;
	color.x = floor(f);
	f = (f-color.x)*256;
	color.y = floor(f);
	color.z = f-color.y;
	color.xy *= 0.00390625; // *= 1.0/256
	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
PixelOutputType DeferredPixelShader(PixelInputType input)
{
	PixelOutputType output;

	output.color = shaderTexture.Sample(SampleTypeWrap, input.tex);
	
	output.normal = float4(input.normal, 1.0f);

	output.specular = float4(0.8f, 0.8f, 0.7f, 1.0f);

	float depth = input.depth.x/input.depth.y;
	output.depth.rgb = float_to_color(depth);
	output.depth.a = 1.0f;

    return output;
}