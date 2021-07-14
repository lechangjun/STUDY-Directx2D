#pragma once
 
class Time
{
private:
	Time(void); // new 할당 불가, Time time 과 같이 생성도 못함
	~Time(void);
 
	static Time* instance;		// 싱글톤 객체, static 이라 한번만 초기화 가능, cpp 전역 위치에 초기화 한번 해주고 할당해주면댐
 
	static bool isTimerStopped;	// 타이머 중지
	static float timeElapsed;	// 이전 프레임으로부터 경과시간
 
 
	INT64 ticksPerSecond;		// 초당 틱카운트
	INT64 currentTime;		// 현재 시간
	INT64 lastTime;			// 이전시간
	INT64 lastFPSUpdate;		// 마지막 FPS 업데이트 시간
	INT64 fpsUpdateInterval;	// fps 업데이트 간격
 
	UINT frameCount;		// 프레임 수
	float runningTime;		// 진행 시간
	float framePerSecond;		// FPS
 
public:
	static Time* Get();		// 객체 얻어오기
 
	static void Create();
	static void Delete();
 
	static bool Stopped() { return isTimerStopped; }
	static float Delta() { return isTimerStopped ? 0.0f : timeElapsed; } // 이전 프레임으로부터 경과시간 반환
 
	void Update();
	void Print();
 
	void Start();
	void Stop();
 
	float FPS() const { return framePerSecond; }    
	float Running() const { return runningTime; }
};