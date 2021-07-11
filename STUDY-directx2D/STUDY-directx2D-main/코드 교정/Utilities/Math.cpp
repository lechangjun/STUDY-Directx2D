#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f; //����

float Math::Modulo(float val1, float val2) 
{
	while (val1 - val2 >= 0)
		val1 -= val2;

	return val1; //va1/val2�� ������ ���ϴ� ����
}

float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f; //������ �������� �ٲٴ� ����
}

float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI; //������ ������ �ٲٴ� ����
}

float Math::Random(float r1, float r2) //r1�� �ּҷ� �ϴ� ������ �Ǽ� �����ϴ� �Լ� (r2�� r1 ���̰� Ŭ ���� �� ���� ������ �� ����)
{
	float random = ((float)rand()) / (float)RAND_MAX; //0~1 ���� �Ǽ�
	float diff = r2 - r1;
	float val = random * diff;
	
	return r1 + val; 
}

float Math::Clamp(float value, float min, float max) //� ���� ������ ���� ���� ������ �������ִ� �Լ�
{
	value = value > max ? max : value; //value�� max���� Ŭ �� value�� max�� ����, �׷��� ������ ���� x
	value = value < min ? min : value; //value�� min���� ���� �� value�� min�� ����, �׷��� ������ ���� x

	return value; 
}

int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1; //r1�� �ּҷ� �ϴ� ������ ���� �����ϴ� �Լ� (r2�� r1 ���̰� Ŭ ���� �� ���� ������ �� ����)
}