#include "stdafx.h"
 
const float Math::PI = 3.14159265f;
 
float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}
 
float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}
 
int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}
 
float Math::Random(float r1, float r2)
{
	/*
	RAND_MAX = 32767
    
	rand() % n 을 쓰게되면 딱 나누어 떨어지지 않는 값으로 인해
	특정 구간의 값이 많이 나오게 된다.
    
	0 ~ n-1 까지의 랜덤값 구하기, 최대 32767까지 구해진다.
	그 이상을 구하기 위해선 다르게 해야한다.
	*/
    
	float diff = r2 - r1;
	float random = ((float)rand()) / (float)RAND_MAX * diff;
 
	return r1 + random;
}