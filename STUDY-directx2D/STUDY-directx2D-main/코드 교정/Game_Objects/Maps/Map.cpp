#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	floors.resize(floorMax);
	floats.resize(floatMax);
	walls.resize(wallMax);
	etcs.resize(elementMax);

	wstring textureFile;
	wstring fileNum;
	string temp;

	textureFile = Textures + L"Hollow_Knight/floor/floor";
	for (int i = 0; i < floors.size(); i++)
	{
		temp = to_string(i + 1);
		fileNum.assign(temp.begin(), temp.end());
		floors[i] = new Sprite(textureFile + fileNum + L".png", shaderFile);
		floors[i]->Scale(1, 1);
	}

	textureFile = Textures + L"Hollow_Knight/float/float";
	for (int i = 0; i < floats.size(); i++)
	{
		temp = to_string(i + 1);
		fileNum.assign(temp.begin(), temp.end());
		floats[i] = new Sprite(textureFile + fileNum + L".png", shaderFile);
	}

	textureFile = Textures + L"Hollow_Knight/wall/wall";
	for (int i = 0; i < walls.size(); i++)
	{
		temp = to_string(i + 1);
		fileNum.assign(temp.begin(), temp.end());
		walls[i] = new Sprite(textureFile + fileNum + L".png", shaderFile);
	}

	textureFile = Textures + L"Hollow_Knight/element/element";
	for (int i = 0; i < etcs.size(); i++)
	{
		temp = to_string(i + 1);
		fileNum.assign(temp.begin(), temp.end());
		etcs[i] = new Sprite(textureFile + fileNum + L".png", shaderFile);
	}
}

Map::~Map()
{
	for (auto floor : floors)
		SAFE_DELETE(floor);
	for (auto _float : floats)
		SAFE_DELETE(_float);
	for (auto wall : walls)
		SAFE_DELETE(wall);
	for (auto etc : etcs)
		SAFE_DELETE(etc);
	for (auto map : maps)
		SAFE_DELETE(map);
}

void Map::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	for (auto floor : floors)
		floor->Update(V, P);
	for (auto _float : floats)
		_float->Update(V, P);
	for (auto wall : walls)
		wall->Update(V, P);
	for (auto etc : etcs)
		etc->Update(V, P);
	for (auto map : maps)
		map->Update(V, P);
}

void Map::Render()
{
	for (auto floor : floors)
		floor->Render();
	for (auto _float : floats)
		_float->Render();
	for (auto wall : walls)
		wall->Render();
	for (auto etc : etcs)
		etc->Render();
	for (auto map : maps)
		map->Render();
}
