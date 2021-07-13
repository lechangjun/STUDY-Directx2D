#include "stdafx.h"
#include "Texture.h"


Texture::Texture(wstring shaderFile, wstring textureFile, D3DXVECTOR2 position, D3DXVECTOR2 scale)
	: Rect(shaderFile, textureFile, position, scale)
	, speed(50.0f), velocity(0.0f), gravity(-1.0f)
	, bOnGround(true)
{
	Trex_Position = Position();
}

Texture::~Texture()
{
}

void Texture::Update()
{
	__super::Update();

	D3DXVECTOR2 position = Position();
	velocity += gravity * Time::Delta();

	if (bOnGround == false)
	{
		position.y += velocity;

		Position(position);
	}

	if (bOnGround == false && position.y < Trex_Position.y) 
		//Á¡ÇÁ ÈÄ °ø·æÀÌ ¹Ù´ÚÀ¸·Î ²¨ÁöÁö¾Ê°Ô
	{
		position.y = Trex_Position.y;
		velocity = 0.0f;

		bOnGround = true;

		Position(position);
	}
}

void Texture::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.5f;
		bOnGround = false;
	}
}

void Texture::EndJump()
{
	if (velocity > 0.9f)
		velocity = 0.8f;
}

void Texture::Go_Left()
{
	D3DXVECTOR2 position = Position();
	position.x -= speed * Time::Delta();

	Position(position);
}
