#pragma once

class Map
{
public:
	Map();
	~Map();

	vector<Sprite*> floors;
	vector<Sprite*> floats;
	vector<Sprite*> walls;
	vector<Sprite*> etcs;
	vector<Sprite*> maps;
	
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();


private:
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	const int floorMax = 14;
	const int floatMax = 11;
	const int wallMax = 11;
	const int elementMax = 12;
};

struct elementDesc
{
	elementDesc() {}
	elementDesc(D3DXVECTOR2 po, int element) { position = po, elementNum = element; }
	
	D3DXVECTOR2 position;
	int elementNum;
};