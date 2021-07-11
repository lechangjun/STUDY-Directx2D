#include "stdafx.h"
#include "Cactus.h"

Cactus::Cactus(wstring shaderFile, wstring textureFile, 
	D3DXVECTOR2 p, D3DXVECTOR2 s, float * sFactor, vector<Cactus*>* h):
	GameObject(p, s), speed(sFactor), holder(h), additionalSpeed(0)
{
	sprite = new Sprite(textureFile, shaderFile);
	sprite->Position(p);

	clip = nullptr;

	trashFlag = false;
}

Cactus::Cactus(wstring shaderFile, wstring textureFile, 
	D3DXVECTOR2 p, D3DXVECTOR2 s, float * sFactor, vector<Cactus*>* h, 
	D3DXVECTOR2 b1st, D3DXVECTOR2 b1ed, D3DXVECTOR2 b2st, D3DXVECTOR2 b2ed, float as):
	GameObject(p, s), speed(sFactor), holder(h), additionalSpeed(as)
{
	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile, shaderFile, b1st.x, b1st.y, b1ed.x, b1ed.y), 0.2f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, b2st.x, b2st.y, b2ed.x, b2ed.y), 0.2f);
	clip->Play();

	sprite = nullptr;

	trashFlag = false;
}

Cactus::~Cactus()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(clip);
}

void Cactus::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	// Shift Ground
	D3DXVECTOR2 pos = Position();
	D3DXVECTOR2 scl = Size();
	pos.x -= ((*speed) + additionalSpeed )* Time::Delta() ;

	//TODO: When cactus is out of place, Remove maybe
	if (pos.x < scl.x / 2 - scl.x) {
		Trash();
		return;
	}

	// Confirm Pos
	Position(pos);

	if (sprite) {
		sprite->Position(Position());
		sprite->Update(V, P);
	}
	else if (clip) {
		clip->Position(Position());
		clip->Update(V, P);
	}
}

void Cactus::Render()
{
	if (sprite)
		sprite->Render();
	else if (clip)
		clip->Render();
}

void Cactus::Trash()
{
	trashFlag = true;
}
