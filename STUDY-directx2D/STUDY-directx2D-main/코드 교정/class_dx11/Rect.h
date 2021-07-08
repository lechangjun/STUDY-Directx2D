#pragma once
 
// 정점위치, 컬러 초기화
// 이동(Translation), 크기(Scaling)
// Buffer->Shader
 
class Rect
{
private:
	D3DXVECTOR2 position;	// Translation
	D3DXVECTOR2 scale;	// Scaling
	D3DXCOLOR color;	// Color
 
public:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXCOLOR Color;
	};
 
private:
	class Shader* shader;
	ID3D11Buffer* vertexBuffer;
 
private:
	void CreateBuffer();
 
public:
	Rect(wstring shaderFile);
	Rect
	(
		wstring shaderFile,
		D3DXVECTOR2 position,
		D3DXVECTOR2 scale,
		D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
	~Rect();
 
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
 
public:
	void Position(float x, float y);		// Setter
	void Position(D3DXVECTOR2 vec);		// Setter(오버로딩)
	D3DXVECTOR2 Position() { return position; }	// Getter
 
	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);
	D3DXVECTOR2 Scale() { return scale; }
 
	void Color(float r, float g, float b);
	void Color(D3DXCOLOR vec);
	D3DXCOLOR Color() { return color; }
};