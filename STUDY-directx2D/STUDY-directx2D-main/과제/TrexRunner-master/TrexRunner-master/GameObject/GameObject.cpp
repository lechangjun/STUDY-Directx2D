#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{
	position = D3DXVECTOR2(0, 0);
	size = D3DXVECTOR2(1, 1);
}

GameObject::GameObject(D3DXVECTOR2 p, D3DXVECTOR2 s)
{
	position = p;
	size = s;
}

GameObject::~GameObject()
{
}

void GameObject::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void GameObject::Position(D3DXVECTOR2 vec)
{
	position = vec;
}

void GameObject::Size(float x, float y)
{
	Size(D3DXVECTOR2(x, y));
}

void GameObject::Size(D3DXVECTOR2 vec)
{
	size = vec;
}

bool GameObject::CollisionCheck(const GameObject & target) const
{
	const int margin = 6;

	if (position.x + size.x / 2 - margin > target.position.x - target.size.x / 2 + margin &&
		position.x - size.x / 2 + margin < target.position.x + target.size.x / 2 - margin &&
		position.y + size.y / 2 - margin > target.position.y - target.size.y / 2 + margin &&
		position.y - size.y / 2 + margin < target.position.y + target.size.y / 2 - margin) {
		return true;
	}
	return false;
}
