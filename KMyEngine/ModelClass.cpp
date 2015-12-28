////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"
#include "GeometryGenerator.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename)
{
	bool result;


	// Load in the model data,
	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	m_mat.Diffuse = XMFLOAT4(0.5f,0.5f,0.5f,1.0f);
	m_mat.Specular = XMFLOAT4(0.8f,0.8f,0.8f,0.05f);
	m_mat.Ambient = XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
	m_mat.Reflect = XMFLOAT4(1.0f,1.0f,1.0f,1.0f);

	return true;
}


void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	GeometryGenerator::MeshData quad;

	GeometryGenerator geoGen;
	geoGen.CreateSphere(1.0f,20,20,quad);

	m_indexCount = quad.Indices.size();
	m_vertexCount = quad.Vertices.size();

	std::vector<VertexType> vertices(quad.Vertices.size());

	for(UINT i = 0; i < quad.Vertices.size(); ++i)
	{
		vertices[i].position   = quad.Vertices[i].Position;
		vertices[i].texture    = quad.Vertices[i].TexC;
		vertices[i].normal     = quad.Vertices[i].Normal;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(VertexType) * quad.Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(device->CreateBuffer(&vbd, &vinitData, &m_vertexBuffer));


	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * quad.Indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &quad.Indices[0];
	HR(device->CreateBuffer(&ibd, &iinitData, &m_indexBuffer));

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType); 
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	result = m_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::ReleaseTexture()
{
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}


bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;

	fin.open(filename);

	if(fin.fail())
	{
		return false;
	}

	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	fin >> m_vertexCount;

	m_indexCount = m_vertexCount;

	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	for(i=0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	fin.close();

	return true;
}


void ModelClass::ReleaseModel()
{
	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}


void ModelClass::SetMaterial(Material mat)
{
	m_mat = mat;
}

Material ModelClass::GetMaterial()
{
	return m_mat;
}

//int fun()
//{
//	//两个fx文件
//	ScreenQuad.fx
//	{
//		struct VertexInput{};
//		struct VertexOutput{};
//		vs
//	}
//
//	RenderLight.fx
//	{
//        #include"ScreenQuad.fx"
//
//		Texture2D gDiffuse : register(t0);
//		Texture2D gNormal  : register(t1);
//
//		SamplerState SampleTypePoint : register(s0);
//
//		struct RenderLightPSOutput
//		{
//			float4 testoutput :  SV_Target0;
//		};
//
//		ps(VertexOutput pin)
//		{
//			gDiffuse.Sample(SampleTypePoint,pin.TexV);
//			gNormal.Sample(SampleTypePoint,pin.TexV);
//		}
//	}
//	EdgeDetectAA.fx
//	{
//		#include"ScreenQuad.fx"
//
//		Texture2D gDiffuse : register(t0);
//		Texture2D gNormal  : register(t1);
//		SamplerState SampleTypePoint : register(s0);
//
//		EdgeDetectAAPSOutput
//		{
//			float4 eaOut : SV_Target0;
//		}
//
//		ps(VertexOutput pin)
//		{
//			gDiffuse.Sample(SampleTypePoint,pin.TexV);
//			gNormal.Sample(SampleTypePoint,pin.TexV);
//		}
//	}
//
//
//	RenderLight.fx
//	{
//         #include"ScreenQuad.fx"
//
//		Texture2D gDiffuse : register(t0);
//		Texture2D gNormal  : register(t1);
//
//		SamplerState SampleTypePoint : register(s0);
//
//		struct RenderLightPSOutput
//		{
//			float4 testoutput :  SV_Target0;
//		};
//
//		ps(VertexOutput pin)
//		{
//			gDiffuse.Sample(SampleTypePoint,pin.TexV);
//			gNormal.Sample(SampleTypePoint,pin.TexV);
//		}
//	}
//
//	EdgeDetectAA.fx
//	{
//        #include"RenderLight.fx"
//
//		//Texture2D gDiffuse : register(t0);
//		//Texture2D gNormal  : register(t1);
//		//SamplerState SampleTypePoint : register(s0);
//
//		EdgeDetectAAPSOutput
//		{
//			float4 eaOut : SV_Target1;
//		}
//
//		ps(VertexOutput pin)
//		{
//			gDiffuse.Sample(SampleTypePoint,pin.TexV);
//			gNormal.Sample(SampleTypePoint,pin.TexV);
//		}
//	}
//
//
//
//
//}