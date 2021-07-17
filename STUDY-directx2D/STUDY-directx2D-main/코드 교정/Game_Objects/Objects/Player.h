#pragma once
#include "Viewer/IFollowing.h"

enum class Direction { Right, Left, Up, Down, Default};

class Player : public IFollowing
{
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size);
	Sprite* GetSprite();

	void StartJump();
	void EndJump();
	void StartDoubleJump();

	D3DXVECTOR2 Position() { return animation->Position(); }
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);

	Animation* GetAnimation() { return animation; }

	bool OnGround() { return bOnGround; }
	void OnGround(bool val) { bOnGround = val; }

	float Velocity() { return velocity; }

	void OnLine(int index, bool val);
	bool* OnLine() { return bOnLine; }

	void LineJump(bool val);
	bool LineJump() { return bLineJump; }

	bool Dash() { return bDash; }

	void DoubleJump(bool val);
	bool DoubleJump() { return bDoubleJump; }

private:
	void Attack(Direction val);

private:
	float moveSpeed;
	float velocity;
	float velocityL;
	float velocityR;
	float gravity;
	
	bool bOnGround;
	bool bOnLine[100];
	bool bLineJump;
	bool bAnimationJump;
	bool bAnimationFall;
	bool bAttackLR;
	bool bAttackUD;
	bool bDash;
	bool bJumpDashCheck;//점프하고 대쉬했는지 체크
	bool bDoubleJump;

	Direction directionLR;//좌우
	Direction directionUD;//상하


	Animation* animation;
	Sprite* attackSprite;
	Sprite* attackSprite2;

	D3DXVECTOR2 position;
	D3DXVECTOR2 focusOffset;
};