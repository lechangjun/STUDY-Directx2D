#include "stdafx.h"
#include "Trex.h"

Trex::Trex(wstring shaderFile, wstring spriteFile, D3DXVECTOR2 pos, float sFactor):
	GameObject(pos, D3DXVECTOR2(44,49)), 
	velocity(0.0f), gravity(-1.0f), strength(0.25f), bOnGround(true), state(0)
{
	// Normal running
	clips[0] = new Clip(PlayMode::Loop);
	clips[0]->AddFrame(new Sprite(spriteFile, shaderFile, 936, 0, 980, 49), 0.2f);
	clips[0]->AddFrame(new Sprite(spriteFile, shaderFile, 980, 0, 1024, 49), 0.2f);
	clips[0]->Play();

	// Crouch running
	clips[1] = new Clip(PlayMode::Loop);
	clips[1]->AddFrame(new Sprite(spriteFile, shaderFile, 1112, 19, 1171, 49), 0.2f);
	clips[1]->AddFrame(new Sprite(spriteFile, shaderFile, 1171, 19, 1230, 49), 0.2f);
	clips[1]->Play();

	// Ouch
	clips[2] = new Clip(PlayMode::End);
	clips[2]->AddFrame(new Sprite(spriteFile, shaderFile, 1024, 0, 1068, 49), 0.2f);
	clips[2]->AddFrame(new Sprite(spriteFile, shaderFile, 1068, 0, 1112, 49), 0.2f);
	clips[2]->Play();
}

Trex::~Trex()
{
	for (int i = 0; i < 3; i++)
		SAFE_DELETE(clips[i]);
}

void Trex::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Trex::Position(D3DXVECTOR2 vec)
{
	for (int i = 0; i < 3; i++) {
		clips[i]->Position(vec);
	}
	__super::Position(vec);
}

void Trex::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 pos = __super::Position();
	D3DXVECTOR2 siz = Size();
	velocity += gravity * Time::Delta();

	if (bOnGround == false) {
		pos.y += velocity;
		Position(pos);
	}
	if (pos.y < siz.y*0.5f + (Height / 2 - 12)) {
		pos.y = siz.y*0.5f + (Height / 2 - 12);
		velocity = 0.0f;

		bOnGround = true;

		Position(pos);
	}

	clips[state]->Update(V, P);
}

void Trex::Render()
{
	clips[state]->Render();
}

void Trex::StartJump()
{
	if (bOnGround == true) {
		velocity = strength;
		bOnGround = false;
	}
}

void Trex::EndJump()
{
	if (velocity > strength / 3)
		velocity = strength / 3;
}

void Trex::StartCrouch()
{
	state = 1;
	Size(59, 30);

	D3DXVECTOR2 p = __super::Position();
	p.x += 6;
	p.y -= 10;
	Position(p);
}

void Trex::EndCrouch()
{
	state = 0;
	Size(44, 49);

	D3DXVECTOR2 p = __super::Position();
	p.x -= 6;
	p.y += 10;
	Position(p);
}
