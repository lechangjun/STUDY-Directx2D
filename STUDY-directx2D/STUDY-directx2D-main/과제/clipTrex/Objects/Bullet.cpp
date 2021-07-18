#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
{
	sprite = new Sprite(Textures + L"Bullets.png", shaderFile, 173, 155, 183, 167);

	position = start;
	sprite->Position(position);

	float radian = Math::ToRadian(angle);
	//x�� cos, y�� sin���� �����ϸ� ���� (3D���� ����)
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);
	velocity *= speed; //�ش� ��������..
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position += velocity;
	//������ ������ �� ��

	sprite->Position(position);
	sprite->Update(V, P);
}

void Bullet::Render()
{
	sprite->Render();
}


