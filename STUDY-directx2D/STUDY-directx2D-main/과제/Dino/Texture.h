#pragma once
#include "Draws/Rect.h"

class Texture : public Rect
{
public:
	Texture(wstring shaderFile, wstring textureFile, D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Texture();

	void Update() override;

	void Speed(float val) { speed = val; }
	float Speed() { return speed; }

	void StartJump();
	void EndJump();

	void Go_Left();

private:
	float speed;

	float velocity;
	float gravity;

	bool bOnGround;

	D3DXVECTOR2 Trex_Position;
};