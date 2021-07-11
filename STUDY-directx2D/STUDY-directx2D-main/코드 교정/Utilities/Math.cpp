#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f; //파이

float Math::Modulo(float val1, float val2) 
{
	while (val1 - val2 >= 0)
		val1 -= val2;

	return val1; //va1/val2의 나머지 구하는 연산
}

float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f; //각도를 라디안으로 바꾸는 연산
}

float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI; //라디안을 각도로 바꾸는 연산
}

float Math::Random(float r1, float r2) //r1을 최소로 하는 랜덤한 실수 생성하는 함수 (r2와 r1 차이가 클 수록 더 넓은 범위의 수 생성)
{
	float random = ((float)rand()) / (float)RAND_MAX; //0~1 사이 실수
	float diff = r2 - r1;
	float val = random * diff;
	
	return r1 + val; 
}

float Math::Clamp(float value, float min, float max) //어떤 값을 정해진 범위 안의 값으로 변경해주는 함수
{
	value = value > max ? max : value; //value가 max보다 클 시 value에 max를 저장, 그렇지 않으면 변경 x
	value = value < min ? min : value; //value가 min보다 작을 시 value에 min을 저장, 그렇지 않으면 변경 x

	return value; 
}

int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1; //r1을 최소로 하는 랜덤한 정수 생성하는 함수 (r2와 r1 차이가 클 수록 더 넓은 범위의 수 생성)
}