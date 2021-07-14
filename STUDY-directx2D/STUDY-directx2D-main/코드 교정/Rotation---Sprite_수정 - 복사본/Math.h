#pragma once
 
class Math
{
private:
 
public:
	static const float PI;
 
	static float ToRadian(float degree);		// Radian으로 변환
	static float ToDegree(float radian);		// Degree로 변환
 
	static int Random(int r1, int r2);		// int random
	static float Random(float r1, float r2);	// float random
 
};