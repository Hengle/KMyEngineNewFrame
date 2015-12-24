////////////////////////////////////////////////////
//
////////////////////////////////////////////////////
cbuffer cbPerObjectVS : register(b0)
{
	float4x4 gWorldViewProj;
}



struct VertexInput
{
    float3 PosL : POSITION;
    float2 Tex  : TEXCOORD0;
};

struct VertexOutput
{
    float4 PosH : SV_POSITION;
    float2 TexV  : TEXCOORD0;
};

VertexOutput DeferredScreenQuadVertexShader(VertexInput vin)
{
    VertexOutput vout;  

    vout.PosH = mul(float4(vin.PosL,1.0f), gWorldViewProj);    
    vout.TexV = vin.Tex;
    
	return vout;
}