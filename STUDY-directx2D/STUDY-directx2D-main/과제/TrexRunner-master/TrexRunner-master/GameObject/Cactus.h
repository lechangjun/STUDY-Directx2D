#pragma once
#include "GameObject.h"

class Cactus : public GameObject
{
public:
	Cactus(wstring shaderFile, wstring textureFile, 
		D3DXVECTOR2 p, D3DXVECTOR2 s, float* sFactor, vector<Cactus*>* h);
	Cactus(wstring shaderFile, wstring textureFile,
		D3DXVECTOR2 p, D3DXVECTOR2 s, float* sFactor, vector<Cactus*>* h,
		D3DXVECTOR2 b1st, D3DXVECTOR2 b1ed, D3DXVECTOR2 b2st, D3DXVECTOR2 b2ed,
		float as);
	virtual ~Cactus();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	void Trash();
public:
	bool trashFlag;
private:
	Sprite* sprite;
	Clip* clip;

	float* speed;
	float additionalSpeed;

	vector<Cactus*>* holder;
};

