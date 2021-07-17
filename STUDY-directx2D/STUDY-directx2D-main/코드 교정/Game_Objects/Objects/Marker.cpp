#include "stdafx.h"
#include "Marker.h"

Marker::Marker(wstring shaderFile, D3DXVECTOR2 start)
{
	clip = new Clip(PlayMode::End);

	clip->AddFrame(new Sprite(Textures + L"Bullets.png", shaderFile, 279, 157, 290, 168), 0.1f);


	position = start;
	clip->Position(position);
	clip->Play();
}

Marker::~Marker()
{
	SAFE_DELETE(clip);
}

void Marker::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	clip->Position(position);
	clip->Update(V, P);
}

void Marker::Render()
{
	clip->Render();
}

void Marker::Position(D3DXVECTOR2 vec)
{
	position = vec;
	clip->Position(position);
}

void Marker::isSelected(bool s)
{
	clip->DrawBound(s);
	isS = s;
}

bool Marker::isSelected() const
{
	return isS;
}