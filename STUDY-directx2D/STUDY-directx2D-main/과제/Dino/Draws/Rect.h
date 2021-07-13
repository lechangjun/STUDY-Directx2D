#pragma once

class Rect
{
public:
	Rect(wstring shaderFile, wstring textureFile);
	Rect(wstring shaderFile, wstring textureFile, D3DXVECTOR2 position, D3DXVECTOR2 scale);
	virtual ~Rect();

	void ViewProjection(D3DXMATRIX& V, D3DXMATRIX& P);

	virtual void Update();
	void Render();

	/////////////////////////////////////////////////

	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

private:
	void CreateBuffer(wstring shaderFile, wstring textureFile);
	void UpdateWorld();

	ID3D11ShaderResourceView* srv;
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};
};
