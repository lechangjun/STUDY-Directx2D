#include "stdafx.h"
#include "Clip.h"

//----------------------------------------------------
// Frame
//----------------------------------------------------

Frame::Frame(Sprite* sprite, float time)
{
	Image = sprite;
	Time = time;
}

Frame::~Frame()
{
	SAFE_DELETE(Image);
}

//----------------------------------------------------
// Clip
//----------------------------------------------------

Clip::Clip(PlayMode mode, float speed)
	: mode(mode), speed(speed)
	, length(0), playTime(0), bPlay(false), currentFrame(0)
{
}

Clip::~Clip()
{
	for (Frame* frame : frames)
		SAFE_DELETE(frame);
}

void Clip::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Clip::Position(D3DXVECTOR2 vec)
{
	for (Frame* frame : frames)
		frame->Image->Position(vec);
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 vec)
{
	for (Frame* frame : frames)
	{
		D3DXVECTOR2 scale = frame->Image->Scale();

		frame->Image->Scale(scale.x * vec.x, scale.y * vec.y); //���� �̹��� �������� ����ϱ�
	}
}

D3DXVECTOR2 Clip::TextureSize()
{
	return frames[currentFrame]->Image->TextureSize();
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	playTime = 0.0f;
	currentFrame = 0;

	bPlay = true; //�÷��� ��
}

void Clip::Play(UINT startFrame)
{
	//�츮�� ���ϴ� �����ӿ��� �����ϰ� �ϱ�
	playTime = 0.0f;
	currentFrame = startFrame;

	bPlay = true;
}

void Clip::Stop()
{
	bPlay = false;
	currentFrame = 0;
}

void Clip::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	Frame* frame = frames[currentFrame];
	frame->Image->Update(V, P);
	
	if (bPlay == false) //false�� update ���� �ʿ䰡 ����
		return; 

	float time = frame->Time * speed; //�ð��� ��� ���ư�
	playTime += Timer->Elapsed();

	//**�м�**
	if (playTime < time)
		return;

	switch (mode)
	{
		case PlayMode::End: //End�� ������ �þ�鼭 ������ ��. �� ������ ���°Ŷ�
		{
			currentFrame++;

			if (currentFrame >= frames.size())
				Stop();
		}
			break;
		case PlayMode::Loop:
		{
			currentFrame++;
			currentFrame %= frames.size(); //**�м�**
		}
			break;
	}

	playTime = 0.0f;
}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}


