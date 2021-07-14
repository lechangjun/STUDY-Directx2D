#include "stdafx.h"
#include "Bullet.h"
 
Bullet::Bullet(wstring textureFile, wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
	:position(0.0f, 0.0f), velocity(0.0f, 0.0f)
{
	bullet = new Sprite(textureFile, shaderFile, 2, 120, 22, 143);
 
	position = start; // 총알 위치
	bullet->Position(position);
	bullet->Scale(1.0f, 1.0f);
 
	// Radian
	radian = Math::ToRadian(angle);
	velocity.x = cosf(radian);	// X 좌표 = Cosθ * 반지름(여기에선 반지름이 1이라 생각하고 생략)
	velocity.y = sinf(radian);	// X 좌표 = Sinθ * 반지름
	velocity *= speed;	// 각도 * 속도
}
 
Bullet::~Bullet()
{
	SAFE_DELETE(bullet);
}
 
void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position += velocity;	// velocity 만큼 이동
 
	if (position.x <= 0 || position.x >= Width)	// 왼쪽, 오른쪽 벽에 닿으면
	{
    	/*
        방법 1
		PI = 3.141592 (라디안)
		position -= velocity;
		radian = Math::PI - radian; // 180 - angle = 튕겨나가는 각도
		velocity.x = cosf(radian)* 빗변(1.0f);	// 빗변(단위벡터)과 각도를 알경우 cos은 밑변 즉 x의 좌표를 구할 수 있다.
        */
 
		//  반사 벡터 : p + 2n(-p*n) ( n : 법선(단위) 벡터)
		velocity.x += 2.0f * -velocity.x;
	}
	else if (position.y <= 0 || position.y >= Height)	// 위, 아래 벽에 닿으면
	{
		velocity.y += -velocity.y * 2.0f;
	}
 
	bullet->Position(position);	// 이동 반영
	bullet->Update(V, P);	// 다시 그려주기
}
 
void Bullet::Render()
{
	bullet->Render();
}