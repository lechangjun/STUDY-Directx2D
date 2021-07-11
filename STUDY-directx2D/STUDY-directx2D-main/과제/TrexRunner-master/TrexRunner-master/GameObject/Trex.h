#pragma once
#include "GameObject.h"

class Trex : public GameObject
{
public:
	Trex(wstring shaderFile, wstring spriteFile, D3DXVECTOR2 pos, float sFactor);
	virtual ~Trex();

	virtual void Position(float x, float y) override;
	virtual void Position(D3DXVECTOR2 vec) override;

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	void StartJump();
	void EndJump();

	void StartCrouch();
	void EndCrouch();
private:
	float velocity;
	float strength;
	float gravity;
	bool bOnGround;

	Clip* clips[3];
	UINT state;
};