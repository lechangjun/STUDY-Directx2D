#include "stdafx.h"
#include "RandomShooter.h"

RandomShooter::RandomShooter(wstring shaderFile, wstring textureFile, 
	vector<Cactus*>* h, float * sf, D3DXVECTOR2 siz,
	D3DXVECTOR2 i, D3DXVECTOR2 p, D3DXVECTOR2 smin, D3DXVECTOR2 smax) :
	holder(h), size(siz),
	interval(i), pivot(p), spreadMin(smin), spreadMax(smax),
	shaderFile(shaderFile), textureFile(textureFile), speedFactor(sf)
{
	isBird = false;
	ResetTimer();
}

RandomShooter::RandomShooter(wstring shaderFile, wstring textureFile,
	vector<Cactus*>* h, float * sf, D3DXVECTOR2 siz,
	D3DXVECTOR2 i, D3DXVECTOR2 p, D3DXVECTOR2 smin, D3DXVECTOR2 smax,
	D3DXVECTOR2 b1st, D3DXVECTOR2 b1ed, D3DXVECTOR2 b2st, D3DXVECTOR2 b2ed) :
	holder(h), size(siz),
	interval(i), pivot(p), spreadMin(smin), spreadMax(smax),
	shaderFile(shaderFile), textureFile(textureFile), speedFactor(sf),
	B1ST(b1st), B1ED(b1ed), B2ST(b2st), B2ED(b2ed)
{
	isBird = true;
	ResetTimer();
}

RandomShooter::~RandomShooter()
{
}

void RandomShooter::Update()
{
	timer += Time::Delta();
	if (timer >= cooltime) {
		if (isBird) {
			holder->push_back(new Cactus(shaderFile, textureFile,
				GetRandomPos(), size, speedFactor, holder,
				B1ST, B1ED, B2ST, B2ED, Math::Random(15, 150)));
		}
		else {
			holder->push_back(new Cactus(shaderFile, textureFile,
				GetRandomPos(), size, speedFactor, holder));
		}
		ResetTimer();
	}
}

void RandomShooter::ResetTimer()
{
	timer = 0;
	cooltime = Math::Random(interval.x, interval.y);
}

D3DXVECTOR2 RandomShooter::GetRandomPos() const
{
	D3DXVECTOR2 p = pivot;
	p.x += Math::Random(spreadMin.x, spreadMax.x);
	p.y += Math::Random(spreadMin.y, spreadMax.y);
	return p;
}
