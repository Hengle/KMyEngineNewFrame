cbuffer cbPerObject : register(b1)
{
	// pixel之间的距离
	float2 gPixelSize;
	// 采样权重
	float gWeight;
	float nouse;
};
// 完成光照之后的图像
Texture2D gFinalColor : register(t0);
Texture2D gNormal	  : register(t1);

SamplerState SampleTypePoint : register(s0);

struct VertexOutput
{
    float4 PosH	 : SV_POSITION;
    float2 TexV  : TEXCOORD;
};


// *** EdgeDetectAA begin ***

float4 psEDAA(VertexOutput pin) : SV_Target
{
	const float2 delta[8] = 
	{
		float2(-1,-1),float2(1,-1),float2(-1,1),float2(1,1),
		float2(-1,0),float2(1,0),float2(0,-1),float2(0,1)
	};
	
	float4 tex = gNormal.Sample(SampleTypePoint,pin.TexV);
	float nfactor = 0.0f;
	//float dfactor = 0.0f;
	
	// 周围4采样normal，决定nfactor
	for(int i = 0;i<4;++i)
	{
		float4 t = gNormal.Sample(SampleTypePoint,pin.TexV + delta[i]*gPixelSize);
		
		t -= tex;
		nfactor += dot(t,t);
	}
	nfactor = min(1.0f,nfactor)*gWeight;
	
	// 周围4采样depth，决定dfactor
	//for(int j = 0;j<4;++j)
	//{
	//	float4 t = tex2D(DepthTexSampler,psin.Tex0+delta[j]*gPixelSize);
	//	
	//	t -= tex;
	//	dfactor += dot(t,t);
	//}
	//dfactor = min(1.0f,dfactor)*gWeight;
	
	float factor = nfactor;//max(nfactor,dfactor);
	
	float4 color = float4(0.0f,0.0f,0.0f,0.0f);
	
	// 周围8采样final color，累加，权重为factor*gWeight*8/10
	for(int k = 0;k<8;++k)
	{
		color += gFinalColor.Sample(SampleTypePoint,pin.TexV+delta[k]*gPixelSize*factor);
	}
	
	// 之间1采样，权重为2/10
	color += gFinalColor.Sample(SampleTypePoint,pin.TexV)*2.0f;
	
	color /= 10.0f;
	
	return color;

}

// === EdgeDetectAA end ===