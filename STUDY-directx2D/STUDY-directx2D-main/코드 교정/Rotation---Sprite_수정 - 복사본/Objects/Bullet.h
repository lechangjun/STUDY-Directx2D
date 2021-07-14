#pragma once
 
class Bullet
{
private:
	class Sprite* bullet;
 
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;
	float radian;
 
public:
	Bullet(wstring textureFile, wstring shaderFile, D3DXVECTOR2 start, float angle, float speed);
	~Bullet();
 
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
};