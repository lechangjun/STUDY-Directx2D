#include "stdafx.h"
#include "Device.h"
#include "Draws/Rect.h"

#include <time.h>

//rect == player
//rect2 == enemies

Rect* rect;
const int num = 77; //Number of other Boxes
Rect* rect2[num];
Math M; //Class Math
int temp = 0; //used in void Render()

void InitScene()
{
	srand(unsigned int(time(NULL)));

	//White Main Box
	rect = new Rect(L"../_Shaders/006_Rect.fx");
	rect->Position(100, 100);
	rect->Scale(100, 100);
	rect->Color(1, 1, 1);

	//Random Scale, Position, Color for other Boxes
	for (int i = 0; i < num; i++)
	{
		rect2[i] = new Rect(L"../_Shaders/006_Rect.fx");

		float ScaleX = M.RandomI(5, 10) * 20.0f;
		float ScaleY = M.RandomI(5, 10) * 20.0f;
		rect2[i]->Scale(ScaleX, ScaleY);

		rect2[i]->Position(-500, -500); //Start at position(-500, 500)
		
		float R = M.RandomI(0, 9) * 0.1f;
		float G = M.RandomI(0, 9) * 0.1f;
		float B = M.RandomI(0, 9) * 0.1f;
		rect2[i]->Color(R, G, B);
	}
}

void DestroyScene()
{
	SAFE_DELETE(rect);
	SAFE_DELETE(rect2[num]);
}

D3DXMATRIX V, P;
void Update()
{
	//Move Key
	if (Key->Press('W') == true)
		rect->MoveUp();
	else if (Key->Press('S') == true)
		rect->MoveDown();
	if (Key->Press('D')==true)
		rect->MoveRight();
	else if (Key->Press('A') == true)
		rect->MoveLeft();

	//잡아먹기
	for (int i = 0; i < num; i++)
	{
		if (rect->xMin() <= rect2[i]->xMax() &&
			rect->xMax() >= rect2[i]->xMin() &&
			rect->yMin() <= rect2[i]->yMax() &&
			rect->yMax() >= rect2[i]->yMin())
		{
			rect2[i]->Position(-500, -500);
			rect->ScaleXup();
			rect->ScaleYup();
			rect->Color(rect2[i]->Color());
		}
	}

	//일정 크기 넘으면 모든 컬러 블랙
	if (rect->Scale().x > 500 &&
		rect->Scale().y > 500)
	{
		rect->Color(0, 0, 0);
		for (int i = 0; i < num; i++)
			rect2[i]->Color(0, 0, 0);
	}

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	rect->ViewProjection(V, P);
	rect->Update();
	for (int i = 0; i < num; i++)
	{
		rect2[i]->ViewProjection(V, P);
		rect2[i]->Update();
	}
}
	
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		rect->Render();

		if (ImGui::Button("Enemy"))
		{
			for (int i = temp; i < temp + 1; i++)
			{
				float x = M.RandomI(0, 900) * 1.0f;
				float y = M.RandomI(0, 800) * 1.0f;
				rect2[i]->Position(x,y);
			}
			temp++;
		}

		for (int i = 0; i < num; i++)
		{
			rect2[i]->Render();
		}
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
