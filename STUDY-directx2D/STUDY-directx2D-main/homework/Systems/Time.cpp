#include "stdafx.h"
#include "Time.h"

Time* Time::instance = NULL;

bool Time::isTimerStopped = true;
float Time::timeElapsed = 0.0f;

Time::Time(void) : //�⺻������
	ticksPerSecond(0), currentTime(0), lastTime(0), lastFPSUpdate(0), fpsUpdateInterval(0),
	frameCount(0), runningTime(0), framePerSecond(0)
	//<--������ �ʱ�ȭ����Ʈ-->
	//ticksPerSecond: �ʴ� ƽ ī��Ʈ
	//currentTime: ���� �ð�
	//lastTime: ���� �ð�
	//lastFPSUpodate: ������ FPS ������Ʈ �ð�
	//fpsUpdateInterval: FPS ������Ʈ ����
	//frameCount: ������ ��
	//runningTime: ���� �ð�
	//framePersecond: FPS (1�ʿ� �����ִ� ȭ���� ��)
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	//<--QueryPerformanceFrequency-->
	//(1)�ڱ� �ý����� �ִ� ��� ���������� timer resolution�� �����ϴ���,
	//   ��� ������ �ð� ��Ȯ���� ������ �ִ���  �Ǻ��ϴµ� ����
	//(2)CPU ���ļ��� ���� 1�ʴ� ����Ǵ� ƽ���� ��Ÿ��. ������ ���� �ѹ��� �о��ָ� ��
	//(3)�Ķ���� = lpPerformanceCount: ���� performance counter�� ���� �����ͷ� ��ȯ��
	//LARGE_INTEGER: 32��Ʈ�� �������� �ʴ� ��뷮 ��꿡 ���̴� ����ü
	//ticksPerSecond��, �� ��ǻ���� Ÿ�̸� ��Ȯ�� & �����쿡�� ���� ���¸� �󸶸��� ������Ʈ �ϴ��� ������
	
	fpsUpdateInterval = ticksPerSecond >> 1;
	// '>>' ������: ������ ����ŭ �������� ��Ʈ���� �̵���Ŵ
	//all bits in fpsUdateInterval shifted left ticksPerSecond

	/*TwBar* bar = TweakBar::Get()->GetBar();
	TwAddVarRO(bar, "Time", TW_TYPE_FLOAT, &framePerSecond, "");*/
}

Time::~Time(void) //�Ҹ���
{

}

Time* Time::Get() //��ü GET�Ҷ�
{
	assert(instance != NULL); //"instance�� NULL���� ���� �ȵ�!"
	
	return instance;
}

void Time::Create() //init
{
	assert(instance == NULL);

	instance = new Time();
}

void Time::Delete() //�Ҹ�
{
	SAFE_DELETE(instance);
}

void Time::Update() //update
{
	if (isTimerStopped) return;

	//1. ����ð��� ������ �ð� ���� �� ���� �ð��� ����Ѵ�.
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)ticksPerSecond;
	runningTime += timeElapsed;


	//2. FPS Update
	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval) //FPS ������Ʈ �ؾ��Ҷ��� �Դٸ�
	{
		float tempCurrentTime = (float)currentTime / (float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)ticksPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime); //�ʴ� �����Ӽ� ����

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0; //������ �� �ʱ�ȭ
	}

	lastTime = currentTime;
}

void Time::Print()
{

}

void Time::Start() //Ÿ�̸Ӱ� �����ִ� ���¿��� ����
{
	if (!isTimerStopped)
		assert(false);

	QueryPerformanceCounter((LARGE_INTEGER *)&lastTime); //lastTime�� ���� �ð��� �־���
	isTimerStopped = false;
}

void Time::Stop() //Ÿ�̸� �帣�� ���¿��� ��ž
{
	if (isTimerStopped)
		assert(false);

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER *)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)ticksPerSecond; //���� �ð����� ���� �ð������� �ð��� �����
	isTimerStopped = true;
}