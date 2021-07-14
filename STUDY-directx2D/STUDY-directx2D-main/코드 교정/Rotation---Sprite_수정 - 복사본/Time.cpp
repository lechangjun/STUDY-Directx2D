#include "stdafx.h"
#include "Time.h"
 
Time* Time::instance = NULL;
 
bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;
 
Time::Time(void) :
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0)
{
	// LARGE_INTEGER 공용체는 부호가 있는 64비트 정수형 데이터를 저장하기 위해 선언된 사용자 정의 데이터 형, 좀 더 정확한 시간값을 저장하기 위함
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond); // QueryPerformanceFrequency() : 1초에 몇번 도는지
	fpsUpdateInterval = ticksPerSecond >> 1;	// fps 업데이트 간격
}
 
Time::~Time(void)
{
 
}
 
Time* Time::Get()
{
	assert(instance != NULL);
	
	return instance;
}
 
void Time::Create()
{
	assert(instance == NULL);
 
	instance = new Time();
}
 
void Time::Delete()
{
	SAFE_DELETE(instance);
}
 
void Time::Update()
{
	if (isTimerStopped) return;
 
	//1. 현재시간을 가져와 시간 간격 및 진행 시간을 계산한다.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime); // 현재 시간을 가져와 currentTime 에 넣는다
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;
 
 
	//2. FPS Update
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);
 
		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}
 
	lastTime = currentTime;
}
 
void Time::Print()
{
 
}
 
void Time::Start()
{
	if (!isTimerStopped)
		assert(false);
 
	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime);
	isTimerStopped = false;
}
 
void Time::Stop()
{
	if (isTimerStopped)
		assert(false);
 
	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond;
	isTimerStopped = true;
}