#pragma once
#include "GameObject.h"

class Ground: GameObject
{
public:
	Ground(wstring shaderFile, wstring textureFile, D3DXVECTOR2 position, float* sFactor);
	virtual ~Ground();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	void SetSpeedFactor(float* s);

private:
	Sprite* sprite;
	float* speed;
};

