#include "stdafx.h"
#include "Time.h"

Time* Time::instance = NULL;

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time(void) : //�⺻ ������
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0)
{	//�ʴ� ƽ ī��Ʈ/���� �ð�/���� �ð�/����FPS ������Ʈ �ð�/������Ʈ ����/
	//������ ��/���� �ð�/�ʴ� ������
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	fpsUpdateInterval = ticksPerSecond >> 1;
	//��Ʈ ������ '>>' : ���������� 1��ŭ ��Ʈ �̵�

	/*TwBar* bar = TweakBar::Get()->GetBar();
	TwAddVarRO(bar, "Time", TW_TYPE_FLOAT, &framePerSecond, "");*/
}

Time::~Time(void)
{

}

Time* Time::Get() //��ü Get
{
	assert(instance != NULL);

	return instance;
}

void Time::Create() //�����Ҵ�
{
	assert(instance == NULL);

	instance = new Time();
}

void Time::Delete() //�Ҹ�
{
	SAFE_DELETE(instance);
}

void Time::Update() //������Ʈ
{
	if (isTimerStopped) return;

	//1. ����ð��� ������ �ð� ���� �� ���� �ð��� ����Ѵ�.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;


	//2. FPS Update
	frameCount++; //�����Ӽ� ����
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime); //������ �� ����

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0; //������ �� �ʱ�ȭ
	}

	lastTime = currentTime;
}

void Time::Print()
{

}

void Time::Start() 
{
	if (!isTimerStopped) //Ÿ�̸Ӱ� �������� ���� ��
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime); //lastTime�� ����ð� ����
	isTimerStopped = false;
}

void Time::Stop()
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond; //���� �ð����� ���� �ð������� �ð� ���
	isTimerStopped = true;
}