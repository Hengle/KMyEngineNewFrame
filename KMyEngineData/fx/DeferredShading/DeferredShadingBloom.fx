
// *** Bloom begin ***
cbuffer cbPerFramePS : register(b0)
{
	float2 gPixelSize;
	float2 nouse;
};

Texture2D gFinalColor : register(t0);
SamplerState SampleTypePoint : register(s0);

#define NUMPOINTS 7

struct VertexOutput
{
    float4 PosH	 : SV_POSITION;
    float2 TexV  : TEXCOORD;
};

struct PSOutputBloom
{
	float4 hBloom : SV_Target0;
	float4 vBloom : SV_Target1;
};

PSOutputBloom psBloom(VertexOutput pin)
{
	float offset[NUMPOINTS] = {0.0f,1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};

	PSOutputBloom pout;
	pout.hBloom = float4(0.0f,0.0f,0.0f,0.0f);
	pout.vBloom = float4(0.0f,0.0f,0.0f,0.0f);

	for( int i=0;i<NUMPOINTS;++i )
	{
		float2 tmp = pin.TexV;
		tmp.x += offset[i]*gPixelSize.x;

		float3 t = gFinalColor.Sample(SampleTypePoint,tmp).xyz;
		pout.vBloom.xyz += dot(t,t);
		
		tmp = pin.TexV;
		tmp.y += offset[i]*gPixelSize.y;
		t = gFinalColor.Sample(SampleTypePoint,tmp).xyz;
		pout.hBloom.xyz += dot(t,t);
	}
	pout.vBloom.xyz *= 1.0/NUMPOINTS;
	pout.hBloom.xyz *= 1.0/NUMPOINTS;
	
	pout.vBloom.w = 1.0f;
	pout.hBloom.w = 1.0f;
	
	return pout;
}

// === Bloom end ===