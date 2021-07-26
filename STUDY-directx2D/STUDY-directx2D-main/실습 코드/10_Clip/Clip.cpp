#include "stdafx.h"
#include "Clip.h"
 
//-----------------------------------------------
//         Frame(Struct)
//-----------------------------------------------
 
 
Frame::Frame(Sprite * sprite, float time)
    :image(sprite), time(time)
{
 
}
 
Frame::~Frame()
{
    SAFE_DELETE(image);
}
 
 
//-----------------------------------------------
//         Clip(Class)
//-----------------------------------------------
 
 
 
Clip::Clip(PlayMode mode, float speed)
    :position(0.0f, 0.0f), scale(1.0f, 1.0f), rotation(0.0f, 0.0f, 0.0f)
    ,length(0.0f), speed(speed), bPlay(false), currentFrame(0), playTime(0.0f)
    ,mode(mode)
{
 
}
 
Clip::~Clip()
{
    for (Frame* frame : frames)
        SAFE_DELETE(frame);        // Frame의 소멸자도 호출되서 image도 지워짐
}
 
 
 
void Clip::Position(float x, float y)
{
    Position(D3DXVECTOR2(x, y));
}
 
void Clip::Position(D3DXVECTOR2 vec)
{
    position = vec;
}
 
void Clip::Scale(float x, float y)
{
    Scale(D3DXVECTOR2(x, y));
}
 
void Clip::Scale(D3DXVECTOR2 vec)
{
    scale = vec;
}
 
void Clip::Rotation(float x, float y, float z)
{
    Rotation(D3DXVECTOR3(x, y, z));
}
 
void Clip::Rotation(D3DXVECTOR3 vec)
{
    rotation = vec;
}
 
void Clip::AddFrame(Sprite * sprite, float time)
{
    frames.push_back(new Frame(sprite, time));
}
 
void Clip::Play()
{
    playTime = 0.0f;
    currentFrame = 0;
    bPlay = true;
}
 
void Clip::Play(UINT startFrame)
{
    playTime = 0.0f;
    currentFrame = startFrame;
    bPlay = true;
}
 
void Clip::Stop()
{
    bPlay = false;
    currentFrame = 0;
}
 
void Clip::Update(D3DXMATRIX V, D3DXMATRIX P)
{
    // 벡터의 현재 프레임을 받아온다
    Frame* frame = frames[currentFrame];
 
    if (bPlay == true)
    {
        float time = frame->time * speed;    // 몇초 띄워줄지
        playTime += Time::Delta();
 
        if (playTime >= time)
        {
            switch (mode)
            {
            case PlayMode::End:
            {
                currentFrame++;
                if (currentFrame >= frames.size())
                    Stop();
            }
            break;
            
            case PlayMode::Loop:
            {
                currentFrame++;
                currentFrame %= frames.size(); // 1 % 3 = 1, 2 % 3 = 2, size() 값과 같은 값이 나올때까지 계속 증가, 같은 값이 나오면 0
            }
            break;
 
            case PlayMode::Reverse:
                break;
            }
            playTime = 0.0f;
 
        }
 
        frames[currentFrame]->image->Position(position);
        frames[currentFrame]->image->Scale(scale);
        frames[currentFrame]->image->Rotation(rotation);
 
        frames[currentFrame]->image->Update(V, P);
    }
}
 
void Clip::Render()
{
    Frame* frame = frames[currentFrame];
    frame->image->Render();
}
