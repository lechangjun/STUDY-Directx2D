#include "stdafx.h"
#include "Player.h"

Player::Player(wstring shaderFile)
	:Rect(shaderFile)
	, speed(0.1f), velocity(0.0f), gravity(-1.5f)
	, bOnGround(true), bAutoMove(false)
{
}

Player::Player(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	:Rect(shaderFile, position, scale, color)
	, speed(0.1f), velocity(0.0f), gravity(-1.5f)
	, bOnGround(true), bAutoMove(false)
{
}

Player::~Player()
{
}

void Player::Update()
{
	__super::Update();

	D3DXVECTOR2 position = Position();
	velocity += gravity * Time::Delta();

	if (bOnGround == false)
	{
		position.y += velocity;

		Position(position);
	}

	if (position.y < Scale().y * 0.5f)
	{
		position.y = Scale().y * 0.5f;
		velocity = 0.0f;

		bOnGround = true;

		Position(position);
	}

	if (bAutoMove == true)
	{
		position.x += speed;
		Position(position);
		if (position.x + Scale().x / 2 >= 1024)
			bAutoMove = false;
	}
	else if (bAutoMove == false)
	{
		position.x -= speed;
		Position(position);
		if (position.x - Scale().x / 2 <= 0)
			bAutoMove = true;
	}
}

void Player::Stop()
{
	speed = 0.0f;
}

void Player::Restart()
{
	speed = 0.1f;
}

//void Player::MoveLeft()
//{
//	D3DXVECTOR2 position = Position();
//	position.x -= speed * Time::Delta();
//
//	Position(position);
//}
//
//void Player::MoveRight()
//{
//	D3DXVECTOR2 position = Position();
//	position.x += speed * Time::Delta();
//
//	Position(position);
//}

void Player::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.8f;
		bOnGround = false;
	}
}

void Player::EndJump()
{
	if (velocity > 0.25f)
		velocity = 0.25f;
}