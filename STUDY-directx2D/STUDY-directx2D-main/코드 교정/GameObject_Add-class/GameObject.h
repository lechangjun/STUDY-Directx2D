#pragma once
class GameObject {
public:
	GameObject();
	GameObject(D3DXVECTOR2 p, D3DXVECTOR2 s);
	virtual ~GameObject();

	virtual void Position(float x, float y);
	virtual void Position(D3DXVECTOR2 vec);
	virtual D3DXVECTOR2 Position() const { return position; }

	virtual void Size(float x, float y);
	virtual void Size(D3DXVECTOR2 vec);
	virtual D3DXVECTOR2 Size() const { return size; }

	bool CollisionCheck(const GameObject& target) const;

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
};