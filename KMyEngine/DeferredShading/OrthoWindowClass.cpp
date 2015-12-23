////////////////////////////////////////////////////////////////////////////////
// Filename: orthowindowclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "orthowindowclass.h"
#include "../GeometryGenerator.h"

OrthoWindowClass::OrthoWindowClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}


OrthoWindowClass::OrthoWindowClass(const OrthoWindowClass& other)
{
}


OrthoWindowClass::~OrthoWindowClass()
{
}


bool OrthoWindowClass::Initialize(ID3D11Device* device, int windowWidth, int windowHeight)
{
	bool result;


	// Initialize the vertex and index buffer that hold the geometry for the ortho window model.
	result = InitializeBuffers(device, windowWidth, windowHeight);
	if(!result)
	{
		return false;
	}

	return true;
}


void OrthoWindowClass::Shutdown()
{
	// Release the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void OrthoWindowClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int OrthoWindowClass::GetIndexCount()
{
	return m_indexCount;
}


bool OrthoWindowClass::InitializeBuffers(ID3D11Device* device, int windowWidth, int windowHeight)
{
	GeometryGenerator::MeshData quad;

	GeometryGenerator geoGen;
	geoGen.CreateFullscreenQuad(quad);

	m_indexCount = quad.Indices.size();
	m_vertexCount = quad.Vertices.size();

	std::vector<VertexType> vertices(quad.Vertices.size());

	for(UINT i = 0; i < quad.Vertices.size(); ++i)
	{
		vertices[i].position   = quad.Vertices[i].Position;
		vertices[i].texture    = quad.Vertices[i].TexC;
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


void OrthoWindowClass::ShutdownBuffers()
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


void OrthoWindowClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}