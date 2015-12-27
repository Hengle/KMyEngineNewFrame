
// *** Merge Output ***

Texture2D gVBloom : register(t0);
Texture2D gHBloom : register(t1);
Texture2D gFinalColorAA : register(t2);

SamplerState SampleTypePoint  : register(s0);
SamplerState SampleTypeLinear : register(s1);

struct VertexOutput
{
    float4 PosH	 : SV_POSITION;
    float2 TexV  : TEXCOORD;
};

float4 psMergeOutput(VertexOutput pin) : SV_Target
{
	float4 vb = gVBloom.Sample(SampleTypePoint,pin.TexV);
	float4 hb = gHBloom.Sample(SampleTypePoint,pin.TexV);
	float4 fc = gFinalColorAA.Sample(SampleTypeLinear,pin.TexV);
	
	float4 rst = fc+(vb*hb);
	return rst;
}

// === Merge Output ===
