#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
	: currentClip(-1), position(0,0), scale(1,1)
{

}

Animation::~Animation()
{
	for (Clip* clip : clips)
		SAFE_DELETE(clip);
}

void Animation::AddClip(Clip * clip)
{
	clips.push_back(clip);
}

void Animation::Play(UINT clipNumber)
{
	if (clipNumber == currentClip)
		return;

	if (currentClip > -1)
		clips[currentClip]->Stop();

	currentClip = clipNumber;
	clips[currentClip]->Play();
}

void Animation::Stop()
{
	if (currentClip > -1)
		clips[currentClip]->Stop();
}

void Animation::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Animation::Position(D3DXVECTOR2 vec)
{
	for (Clip* clip : clips)
		clip->Position(vec);

	position = vec;
}

void Animation::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Animation::Scale(D3DXVECTOR2 vec)
{
	for (Clip* clip : clips)
		clip->Scale(vec);

	scale = vec;
}

D3DXVECTOR2 Animation::TextureSize()
{
	if (currentClip < 0)
		return D3DXVECTOR2(0, 0);

	return clips[currentClip]->TextureSize();
}

void Animation::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (currentClip < 0)
		return;

	clips[currentClip]->Update(V, P);
}

void Animation::Render()
{
	if (currentClip < 0)
		return;

	clips[currentClip]->Render();
}
