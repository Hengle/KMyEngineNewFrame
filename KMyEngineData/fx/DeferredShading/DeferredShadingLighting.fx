// *** Light stage begin ***
// view space 

cbuffer cbPerFramePS : register(b1)
{
	float3 gLightDirV;
	float nouse;

	float4 gDiffuseLight;
	float4 gSpecularLight;

	float4x4 gProjMatrix;
};

Texture2D gDiffuse  : register(t0);
Texture2D gNormal	: register(t1);
Texture2D gSpecular : register(t2);
Texture2D gDepth	: register(t3);

struct VertexOutput
{
    float4 PosH	 : SV_POSITION;
    float2 TexV  : TEXCOORD;
};

SamplerState SampleTypePoint : register(s0);

float NrmDevZToViewZ(float nz)
{
	float a = gProjMatrix[2].z;
	float b = gProjMatrix[3].z;
	
	float vz = b/(nz-a);
	return vz;	
}

float NrmDevXToViewX(float nx,float vz)
{
	float a = gProjMatrix[0].x;
	
	float vx = (nx*vz)/a;;
	return vx;
}

float NrmDevYToViewY(float ny,float vz)
{
	float a = gProjMatrix[1].y;
	// ny = vy/(vz*a)
	float vy = (ny*vz)/a;
	return vy;
}

float color_to_float(float3 color)
{
	const float3 byte_to_float=float3(1.0,1.0/256,1.0/(256*256));
	return dot(color,byte_to_float);
}

// psLighting()
// uses data from textures (previous render targets)
float4 psLightStage(VertexOutput pin) : SV_Target
{
		float2 texcoord = pin.TexV  ;
	float4 depthSample = gDepth.Sample(SampleTypePoint,texcoord);
	
	// depth texture保存normalized device coordinate的depth值
	float ndcDepth = clamp(color_to_float(depthSample.xyz),0.0f,1.0f);
	
	// 计算(恢复)在view space coordinate内的坐标
	float3 vPos;
	vPos.z = NrmDevZToViewZ(ndcDepth);
	vPos.x = NrmDevXToViewX(pin.TexV  .x*2.0f-1.0f,vPos.z);
	vPos.y = NrmDevYToViewY(-(pin.TexV  .y*2.0f-1.0f),vPos.z);

	// Normal(view space)
	float4 vNormal = gNormal.Sample(SampleTypePoint,pin.TexV  )*2.0f-1.0f;
	float4 diffuse = gDiffuse.Sample(SampleTypePoint,pin.TexV  );	
	float4 specular = gSpecular.Sample(SampleTypePoint,pin.TexV  );
	
	// 注：在view space计算光照，所以eyePos=（0，0，0）
	// lookAt = vPos-eyePos = vPos
	// toEye = eyePos-vPos = -vPos
	
	//=================================================================
	float3 toEye = normalize(float3(0.0f,0.0f,0.0f)-vPos);
	
	float3 r = reflect(gLightDirV,normalize(vNormal.xyz));
	
	float t = pow(max(dot(r,toEye),0.0f),specular.w*1000.0f);
	
	float s = max(dot(-gLightDirV,vNormal.xyz),0.0f);
	
	float3 specColor = t*(specular.xyz*gSpecularLight);
	float3 diffuseColor = s*(diffuse.xyz*gDiffuseLight);
	float3 ambientColor = (diffuse.xyz*gDiffuseLight)*0.3f;
	
	float4 outColor;
	outColor.xyz = specColor+diffuseColor+ambientColor;
	outColor.a = 1.0f;
	
	return outColor;

}