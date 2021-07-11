#pragma once

enum class PlayMode {
	End = 0,Loop,Reverse
};

struct Frame {
	float Time;
	Sprite* Image;

	Frame(Sprite* sprite, float time);
	virtual ~Frame();
};

class Clip {
public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
	virtual ~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	float length;
	float speed;

	bool bPlay;
	UINT currentFrame;
	float playTime;

	PlayMode mode;

	vector<Frame*> frames;

	D3DXVECTOR2 position;
};