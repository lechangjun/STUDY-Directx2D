#include "stdafx.h"
#include "Player.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(200.0f), focusOffset(-500, -540), bOnGround(true), velocity(0.0f), gravity(-1.5f), position(position),
	bLineJump(false), bAnimationJump(false), bAnimationFall(false), bAttackLR(false), bAttackUD(false), bDash(false),
	velocityL(0.0f), velocityR(0.0f), bJumpDashCheck(false), bDoubleJump(false)
{
	animation = new Animation();

	wstring spriteFile1 = Textures + L"/Hollow_Knight/TheKnight01.png";
	wstring spriteFile2 = Textures + L"/Hollow_Knight/TheKnight02.png";
	wstring spriteFile3 = Textures + L"/Hollow_Knight/TheKnight03.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	//Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1656, 3604, 1716, 3732), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1683, 3470, 1743, 3598), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1618, 3470, 1678, 3598), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1554, 3470, 1614, 3598), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1527, 3604, 1587, 3732), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1592, 3604, 1652, 3732), 0.3f);
		animation->AddClip(clip);
	}

	//Run
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 653, 3608, 711, 3732), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 821, 3837, 885, 3961), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 918, 3607, 983, 3732), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 689, 3839, 751, 3962), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1375, 3604, 1437, 3732), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1400, 3473, 1464, 3597), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1375, 3604, 1437, 3732), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 689, 3839, 751, 3962), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 918, 3607, 983, 3732), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 821, 3837, 885, 3961), 0.1f);
		animation->AddClip(clip);
	}
	
	//Jump
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 1961, 94, 2020, 214), 0.025f);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 1398, 105, 1467, 220), 0.025f);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 2100, 94, 2177, 214), 0.05f);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 1893, 221, 1969, 339), 0.05f);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 2184, 92, 2249, 210), 0.3f);
		animation->AddClip(clip);
	}

	//Fall
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 4, 2347, 84, 2458), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 4, 2589, 84, 2709), 0.3f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 4, 2968, 84, 3088), 0.3f);
		animation->AddClip(clip);
	}

	//AttackLR
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 2880, 1029, 2967, 1153), 0.2f);
		animation->AddClip(clip);
	}

	//AttackTop
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 463, 282, 545, 380), 0.2f);
		animation->AddClip(clip);
	}

	//AttackBottom
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1307, 869, 1433, 982), 0.2f);
		animation->AddClip(clip);
	}

	//Dash
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 276, 3970, 361, 4089), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 364, 3970, 449, 4092), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 552, 3984, 655, 4092), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1454, 868, 1621, 981), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 552, 3984, 655, 4092), 0.1f);
		animation->AddClip(clip);
	}

	//DoubleJump
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 2471, 3597, 2576, 3732), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1301, 1662, 1418, 1779), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1074, 1239, 1144, 1371), 0.1f);
		clip->AddFrame(new Sprite(spriteFile3, shaderFile, 1783, 1114, 1876, 1230), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 1301, 1662, 1418, 1779), 0.1f);
		clip->AddFrame(new Sprite(spriteFile2, shaderFile, 2471, 3597, 2576, 3732), 0.1f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);

	attackSprite = new Sprite(spriteFile1, shaderFile, 1742, 1531, 1900, 1674);
	attackSprite->Position(6000, 6000);
	attackSprite->Scale(1, 1);

	attackSprite2 = new Sprite(spriteFile1, shaderFile, 1502, 1448, 1587, 1571);
	attackSprite2->Position(6000, 6000);
	attackSprite2->Scale(1.5f, 1.5f);

	for (int i = 0; i < 100; i++)
		bOnLine[i] = false;

	animation->DrawBound(true);

	directionLR = Direction::Right;
	directionUD = Direction::Default;
}

Player::~Player()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(attackSprite)
	SAFE_DELETE(attackSprite2)
}



void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 po = animation->Position();

	if (bOnGround == true)
	{
		velocity = 0.0f;
		bAnimationJump = false;
		bAnimationFall = false;
		bJumpDashCheck = false;
		bDoubleJump = false;
	}


	bool bMove = false;
	if (bDash == false)
	{
		if (Key->Press(VK_LEFT))
		{
			bMove = true;
			po.x -= moveSpeed * Timer->Elapsed();
			animation->RotationDegree(0, 180, 0);

			directionLR = Direction::Left;
		}
		else if (Key->Press(VK_RIGHT))
		{
			bMove = true;
			po.x += moveSpeed * Timer->Elapsed();
			animation->RotationDegree(0, 0, 0);
			directionLR = Direction::Right;
		}
	}
	

	if (Key->Down(VK_UP))
	{
		directionUD = Direction::Up;
	}
	else if (Key->Up(VK_UP))
	{
		directionUD = Direction::Default;
	}

	if (Key->Down(VK_DOWN))
	{
		directionUD = Direction::Down;
	}
	else if(Key->Up(VK_DOWN))
	{
		directionUD = Direction::Default;
	}

	//if (Key->Down('Z'))
	//{
	//	StartJump();
	//}
	//else if (Key->Up('Z'))
	//{
	//	EndJump();
	//}
	if (bOnGround == false && velocityL == 0.0f && velocityR == 0.0f)
	{
		velocity += gravity * Timer->Elapsed();
		po.y += velocity;
		animation->Position(po);
	}


	animation->Position(po);
	if (bAnimationJump == false && bDash == false)
	{
		animation->Play(bMove ? 1 : 0);
	}
	if (bAnimationJump == true)
	{
		if (velocity < 0.0f && bAnimationFall == false)
		{
			bAnimationFall == true;
			animation->Play(3);
		}
	}
	if (Key->Down('X'))//АјАн
	{
		if (bDash == false)
		{
			if (directionUD == Direction::Default)
			{
				Attack(directionLR);
			}
			else
			{
				Attack(directionUD);
			}
		}
	}
	else if (Key->Up('X'))
	{
		bAttackLR = false;
		bAttackUD = false;
	}
	if (bAttackLR == true)
		animation->Play(4);
	if (bAttackUD == true)
	{
		if (directionUD == Direction::Up)
			animation->Play(5);
		else if (directionUD == Direction::Down)
			animation->Play(6);
	}
	
	//Dash
	if (Key->Down('C'))
	{
		if (bDash == false && bJumpDashCheck == false)
		{
			bDash = true;
			velocity = 0.0f;
			if (directionLR == Direction::Left)
				velocityL = -0.7;
			else if (directionLR == Direction::Right)
				velocityR = 0.7;
			if (bOnGround == false && bJumpDashCheck == false)
			{
				bJumpDashCheck = true;
			}
			animation->Play(7);
		}
	}
	if (velocityL < 0.0f)
	{
		velocityL += 1.0f * Timer->Elapsed();
		po.x += velocityL;
		animation->Position(po);
		if (velocityL >= 0.0f)
		{
			velocityL = 0.0f;
			if (velocityR == 0.0f)
			{
				bDash = false;
				if (bJumpDashCheck == true)
				{
					bAnimationJump = true;
				}
			}
		}
	}


	if (velocityR > 0.0f)
	{
		velocityR -= 1.0f * Timer->Elapsed();
		po.x += velocityR;
		animation->Position(po);
		if (velocityR <= 0.0f)
		{
			velocityR = 0.0f;
			if (velocityL == 0.0f)
			{
				bDash = false;
				if (bJumpDashCheck == true)
				{
					bAnimationJump = true;
				}
			}
		}
	}

	//DoubleJump
	if (bOnGround == false && velocity < 0.0f && bDoubleJump == false)
	{
		if (Key->Down('Z') && bDoubleJump == false)
		{
			bDoubleJump = true;
			StartDoubleJump();
		}
		else if (Key->Up('Z'))
		{
			EndJump();
		}
		
	}
	if (bDoubleJump == true && velocity > 0.0f)
		animation->Play(8);


	animation->Update(V, P);
	if (bAttackLR == true)
		attackSprite->Update(V, P);

	if (bAttackUD == true)
		attackSprite2->Update(V, P);
}

void Player::Render()
{
	ImGui::SliderFloat("Move Speed", &moveSpeed, 50, 400);
	if (ImGui::Button("OnGround"))
	{
		if (bOnGround == true)
			bOnGround = false;
		else
			bOnGround = true;
	}
	ImGui::LabelText("UP Down", directionUD == Direction::Up ? "Up" : "Down");

	animation->Render();
	if (bAttackLR == true)
		attackSprite->Render();

	if (bAttackUD == true)
		attackSprite2->Render();
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;

	//D3DXVECTOR2 textureSize = animation->TextureSize();
	//D3DXVECTOR2 scale = animation->Scale();

	//(*size).x = textureSize.x * scale.x;
	//(*size).y = textureSize.y * scale.y;
	(*size) = D3DXVECTOR2(1, 1);
}

Sprite * Player::GetSprite()
{
	return animation->GetSprite();
}

void Player::StartJump()
{
	if (bOnGround == true)
	{
		velocity = 0.75;
		bOnGround = false;
		bAnimationJump = true;
		animation->Play(2);
	}
}

void Player::EndJump()
{
	if (velocity > 0.25f)
		velocity = 0.25f;
}

void Player::StartDoubleJump()
{
	velocity = 0.75;
	bOnGround = false;
	bAnimationJump = true;
}

void Player::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Player::Position(D3DXVECTOR2 & vec)
{
	position = vec;
	animation->Position(position);
}

void Player::OnLine(int index, bool val)
{
	bOnLine[index] = val;
}

void Player::LineJump(bool val)
{
	bLineJump = val;
}

void Player::DoubleJump(bool val)
{
	bDoubleJump = val;
}

void Player::Attack(Direction val)
{
	float playerRight = animation->Position().x + animation->TextureSize().x * animation->Scale().x * 0.5;
	float playerLeft = animation->Position().x - animation->TextureSize().x * animation->Scale().x * 0.5;
	float playerTop = animation->Position().y + animation->TextureSize().y * animation->Scale().y * 0.5;
	float playerBottom = animation->Position().y - animation->TextureSize().y * animation->Scale().y * 0.5;

	switch (val)
	{
	case Direction::Right:
		bAttackLR = true;
		attackSprite->RotationDegree(0, 0, 0);
		attackSprite->Position(playerRight + attackSprite->TextureSize().x * attackSprite->Scale().x * 0.25, animation->Position().y);
		animation->RotationDegree(0, 0, 0);
		break;
	case Direction::Left:
		bAttackLR = true;
		attackSprite->RotationDegree(0, 180, 0);
		attackSprite->Position(playerLeft - attackSprite->TextureSize().x * attackSprite->Scale().x * 0.25, animation->Position().y);
		animation->RotationDegree(0, 180, 0);
		break;
	case Direction::Up:
		bAttackUD = true;
		if (directionLR == Direction::Right)
			attackSprite2->RotationDegree(180, 0, 0);
		else if (directionLR == Direction::Left)
			attackSprite2->RotationDegree(180, 180, 0);
		attackSprite2->Position(animation->Position().x, playerTop + attackSprite2->TextureSize().y * attackSprite2->Scale().y * 0.25);
		break;
	case Direction::Down:
		if (bOnGround == false)
		{
			bAttackUD = true;
			if (directionLR == Direction::Right)
				attackSprite2->RotationDegree(0, 0, 0);
			else if (directionLR == Direction::Left)
				attackSprite2->RotationDegree(0, 180, 0);
			attackSprite2->Position(animation->Position().x, playerBottom - attackSprite2->TextureSize().y * attackSprite2->Scale().y * 0.25);
		}
		break;
	default:
		break;
	}
}


