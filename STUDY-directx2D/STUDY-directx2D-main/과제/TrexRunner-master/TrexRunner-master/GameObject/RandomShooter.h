#pragma once
#include "./GameObject/Cactus.h"

/// This clss randomly generate cactus and flying cactus
class RandomShooter {
public:
	RandomShooter(wstring shaderFile, wstring textureFile,
		vector<Cactus*>* h, float* sf, D3DXVECTOR2 siz,
		D3DXVECTOR2 i, D3DXVECTOR2 p, D3DXVECTOR2 smin, D3DXVECTOR2 smax);

	RandomShooter(wstring shaderFile, wstring textureFile,
		vector<Cactus*>* h, float* sf, D3DXVECTOR2 siz,
		D3DXVECTOR2 i, D3DXVECTOR2 p, D3DXVECTOR2 smin, D3DXVECTOR2 smax,
		D3DXVECTOR2 b1st, D3DXVECTOR2 b1ed, D3DXVECTOR2 b2st, D3DXVECTOR2 b2ed
	);

	~RandomShooter();

	void Update();

private:
	void ResetTimer();
	D3DXVECTOR2 GetRandomPos() const;

private:
	bool isBird;
	D3DXVECTOR2 B1ST, B1ED, B2ST, B2ED;

	float timer;
	float cooltime;

	D3DXVECTOR2 interval;
	D3DXVECTOR2 pivot;
	D3DXVECTOR2 spreadMin;
	D3DXVECTOR2 spreadMax;

	vector<Cactus*>* holder;

	wstring shaderFile;
	wstring textureFile;
	D3DXVECTOR2 size;
	float* speedFactor;
};