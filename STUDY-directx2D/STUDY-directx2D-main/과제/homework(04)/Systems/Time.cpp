#include "stdafx.h"
#include "Time.h"

Time* Time::instance = NULL;

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time(void) : //기본 생성자
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0)
{	//초당 틱 카운트/현재 시간/이전 시간/이전FPS 업데이트 시간/업데이트 간격/
	//프레임 수/진행 시간/초당 프레임
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	fpsUpdateInterval = ticksPerSecond >> 1;
	//비트 연산자 '>>' : 오른쪽으로 1만큼 비트 이동

	/*TwBar* bar = TweakBar::Get()->GetBar();
	TwAddVarRO(bar, "Time", TW_TYPE_FLOAT, &framePerSecond, "");*/
}

Time::~Time(void)
{

}

Time* Time::Get() //객체 Get
{
	assert(instance != NULL);

	return instance;
}

void Time::Create() //동적할당
{
	assert(instance == NULL);

	instance = new Time();
}

void Time::Delete() //소멸
{
	SAFE_DELETE(instance);
}

void Time::Update() //업데이트
{
	if (isTimerStopped) return;

	//1. 현재시간을 가져와 시간 간격 및 진행 시간을 계산한다.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;


	//2. FPS Update
	frameCount++; //프레임수 증가
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime); //프레임 수 갱신

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0; //프레임 수 초기화
	}

	lastTime = currentTime;
}

void Time::Print()
{

}

void Time::Start() 
{
	if (!isTimerStopped) //타이머가 멈춰있지 않을 때
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime); //lastTime에 현재시간 넣음
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond; //이전 시간부터 멈춘 시간까지의 시간 계산
	isTimerStopped = true;
}