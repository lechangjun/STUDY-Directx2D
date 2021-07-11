#include "stdafx.h"
#include "Ground.h"

Ground::Ground(wstring shaderFile, wstring textureFile, D3DXVECTOR2 position, float* sFactor):
	GameObject(position, D3DXVECTOR2(1200,12)), speed(sFactor)
{
	sprite = new Sprite(textureFile, shaderFile);
	sprite->Position(position);
}

Ground::~Ground()
{
	SAFE_DELETE(sprite);
}

void Ground::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	// Shift Ground
	D3DXVECTOR2 pos = Position();
	D3DXVECTOR2 scl = Size();
	pos.x -= (*speed)* Time::Delta();

	// When ground is out of place, return cartridge
	if (pos.x < scl.x / 2 - 1200) {
		pos.x += 2400;
	}

	// Confirm Pos
	Position(pos);

	sprite->Position(Position());
	sprite->Update(V, P);
}

void Ground::Render()
{
	sprite->Render();
}

void Ground::SetSpeedFactor(float* s)
{
	speed = s;
}
