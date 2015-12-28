
// *** Merge Output ***

Texture2D gOutputTextures : register(t0);
SamplerState SampleTypeLinear : register(s1);

struct VertexOutput
{
    float4 PosH	 : SV_POSITION;
    float2 TexV  : TEXCOORD;
};

float4 psMergeOutput(VertexOutput pin) : SV_Target
{
	float4 outColor;
		outColor = gOutputTextures.Sample(SampleTypeLinear,pin.TexV);

	return outColor;
}

// === Merge Output ===
