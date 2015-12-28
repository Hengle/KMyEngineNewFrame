#include"../LightHelper.fx"
cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
	float4x4 gWorldView;

	Material gMaterial;
};

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

struct VertexInput
{
    float3 PosL		: POSITION;
	float3 NormalL	: NORMAL;
    float2 Tex		: TEXCOORD0;	
};

struct VertexOutput
{
    float4 PosH		: SV_POSITION;
	float3 NormalV  : NORMAL;
    float2 Tex		: TEXCOORD0;
	
	float2 Depth	: TEXCOORD1;
};

struct PixelOutput
{
    float4 color	: SV_Target0;
    float4 normalV	: SV_Target1;
	float4 specular	: SV_Target2;
	float4 depth	: SV_Target3;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
VertexOutput DeferredVertexShader(VertexInput vin)
{
    VertexOutput vout;   

    vout.PosH	  = mul(float4(vin.PosL,1.0f),gWorldViewProj);
	vout.NormalV  = mul(float4(vin.NormalL,0.0f), gWorldView).xyz;    
    vout.Tex	  = vin.Tex;    
	vout.Depth    = vout.PosH.zw;

	return vout;
}

float3 float_to_color( float f)
{
	float3 color;
	f *= 256;
	color.x = floor(f);
	f = (f-color.x)*256;
	color.y = floor(f);
	color.z = f-color.y;
	color.xy *= 0.00390625; // *= 1.0/256S
	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
PixelOutput DeferredPixelShader(VertexOutput pin)
{
	PixelOutput pout;

	pin.NormalV = normalize(pin.NormalV);		
	//[-1,1] -> [0,1]
	pout.normalV.xyz = pin.NormalV*0.5f+0.5f;
	pout.normalV.w = 1.0f;

	pout.color = shaderTexture.Sample(SampleTypeWrap, pin.Tex);
	pout.color.a = 1.0f;

	pout.specular = gMaterial.Specular;

	float depth = pin.Depth.x/pin.Depth.y;
	pout.depth.rgb = float_to_color(depth);
	pout.depth.a = 1.0f;

    return pout;
}