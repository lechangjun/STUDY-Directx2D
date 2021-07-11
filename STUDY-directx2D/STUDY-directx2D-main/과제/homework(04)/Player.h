#pragma once
#include "Draws/Rect.h"

class Player : public Rect
{
public:
	Player(wstring shaderFile);
	Player(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color=D3DXCOLOR(1,1,1,1));
	~Player();

	void Update() override;

	//void MoveLeft();
	//void MoveRight();
	void Stop();
	void Restart();

	void Speed(float val) { speed = val; }
	float Speed() { return speed; }

	void StartJump();
	void EndJump();

	float* pSpeed() { return &speed; }

private:
	float speed;

	float velocity;
	float gravity;
	bool bOnGround;

	bool bAutoMove;
};