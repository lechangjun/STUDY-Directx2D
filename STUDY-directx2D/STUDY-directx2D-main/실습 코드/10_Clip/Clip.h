#pragma once
 
// PlayMode::END 이렇게 사용 그냥 enum은 END 바로 사용가능
enum class PlayMode { End = 0, Loop, Reverse };

 
struct Frame
{
    Sprite* image;
    float time;    // 그림 한장을 띄워주기 위한 시간, 너무 빠르면 애니메이션이 보이지 않는다.
 
    Frame(Sprite* sprite, float time);
    ~Frame();
};
 
 
class Clip
{
private:
    // Sprite의 position, scale, rotation 설정 값
    D3DXVECTOR2 position;
    D3DXVECTOR2 scale;
    D3DXVECTOR3 rotation;
 
    float length;            // 클립의 전체 길이
    float speed;            // 배속
    bool bPlay;                // 재생중인지
    UINT currentFrame;        // 현재 플레이 중인 프레임 번호
    float playTime;            // 너무 빨리 재생되는것을 방지(Delta Time)
 
    PlayMode mode;            // 무슨 모드인지 저장
 
    vector<Frame*> frames;    // Frame을 여러장 보관할 벡터
 
public:
    Clip(PlayMode mode = PlayMode::End, float speed = 1.0f);
    ~Clip();
 
    void Position(float x, float y);
    void Position(D3DXVECTOR2 vec);
    D3DXVECTOR2 Position() { return position; }
 
    void Scale(float x, float y);
    void Scale(D3DXVECTOR2 vec);
    D3DXVECTOR2 Scale() { return scale; }
 
    void Rotation(float x, float y, float z);
    void Rotation(D3DXVECTOR3 vec);
    D3DXVECTOR3 Rotation() { return rotation; }
 
    // 외부에서 프레임을 추가 할 수 있도록 하는 함수
    void AddFrame(Sprite* sprite, float time);
    
    // 재생, 정지
    void Play();
    void Play(UINT startFrame);    // 특정 위치에서 시작
    void Stop();
 
    void Update(D3DXMATRIX V, D3DXMATRIX P);
    void Render();
};
