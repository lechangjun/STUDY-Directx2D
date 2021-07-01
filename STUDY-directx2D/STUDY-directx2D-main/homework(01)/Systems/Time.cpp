#include "stdafx.h"
#include "Time.h"

Time* Time::instance = NULL;

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time(void) : //기본생성자
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0)
	//<--생성자 초기화리스트-->
	//ticksPerSecond: 초당 틱 카운트
	//currentTime: 현재 시간
	//lastTime: 이전 시간
	//lastFPSUpodate: 마지막 FPS 업데이트 시간
	//fpsUpdateInterval: FPS 업데이트 간격
	//frameCount: 프레임 수
	//runningTime: 진행 시간
	//framePersecond: FPS (1초에 보여주는 화면의 수)
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	//<--QueryPerformanceFrequency-->
	//(1)자기 시스템이 최대 어느 정도까지의 timer resolution을 지원하는지,
	//   어느 정도의 시간 정확도를 가지고 있는지  판별하는데 쓰임
	//(2)CPU 주파수에 따른 1초당 진행되는 틱수를 나타냄. 변동이 없어 한번만 읽어주면 됨
	//(3)파라미터 = lpPerformanceCount: 현재 performance counter의 값을 포인터로 반환함
	//LARGE_INTEGER: 32비트로 지원되지 않는 대용량 계산에 쓰이는 구조체
	//ticksPerSecond에, 내 컴퓨터의 타이머 정확도 & 윈도우에서 현재 상태를 얼마마다 업데이트 하는지 저장함
	
	fpsUpdateInterval = ticksPerSecond >> 1;
	// '>>' 연산자: 지정한 수만큼 왼쪽으로 비트들을 이동시킴
	//all bits in fpsUdateInterval shifted left ticksPerSecond

	/*TwBar* bar = TweakBar::Get()->GetBar();
	TwAddVarRO(bar, "Time", TW_TYPE_FLOAT, &framePerSecond, "");*/
}

Time::~Time(void) //소멸자
{

}

Time* Time::Get() //객체 GET할때
{
	assert(instance != NULL); //"instance에 NULL값이 들어가면 안됨!"
	
	return instance;
}

void Time::Create() //init
{
	assert(instance == NULL);

	instance = new Time();
}

void Time::Delete() //소멸
{
	SAFE_DELETE(instance);
}

void Time::Update() //update
{
	if (isTimerStopped) return;

	//1. 현재시간을 가져와 시간 간격 및 진행 시간을 계산한다.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;


	//2. FPS Update
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval) //FPS 업데이트 해야할때가 왔다면
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime); //초당 프레임수 갱신

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0; //프레임 수 초기화
	}

	lastTime = currentTime;
}

void Time::Print()
{

}

void Time::Start() //타이머가 멈춰있는 상태에서 ㄱㄱ
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime); //lastTime에 현재 시간을 넣어줌
	isTimerStopped = false;
}

void Time::Stop() //타이머 흐르는 상태에서 스탑
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond; //이전 시간부터 멈춘 시간까지의 시간을 계산함
	isTimerStopped = true;
}