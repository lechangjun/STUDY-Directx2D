#pragma once

enum class PlayMode //�÷��� ��� ���ϱ�
{
	End = 0, //���۵��� �ѹ� ����ϰ� ��������
	Loop, //�ݺ�
	Reverse //����
};

struct Frame //����ü�� ������ó�� ��������
{
	float Time; //�������� �����ϱ� ���� �ð�
	Sprite* Image;

	Frame(Sprite* sprite, float time);
	~Frame();
};

class Clip
{
public:
	Clip(PlayMode mode = PlayMode::End, float speed = 1.0f); //default parameter�� End
	~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 vec);

	D3DXVECTOR2 TextureSize();

	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	float length; //�ش� Ŭ���� ���� ��ü ����
	float speed;

	bool bPlay; //���� Ŭ���� ��� ������ �ƴ��� �Ǵ��Ϸ��� bPlay
	UINT currentFrame; //����ǰ� �ִ� ���� �������� ��������
	float playTime;

	PlayMode mode; //���� ���� PlayMode

	vector<Frame *> frames; //�������� �𿩼� �ϳ��� Ŭ���� ��
};


