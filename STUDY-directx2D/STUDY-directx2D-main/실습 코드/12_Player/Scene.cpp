#include "stdafx.h"
#include "Device.h"
#include "Objects/Background.h"
#include "Objects/Player.h"



Background* bg;
Player* player;
Sprite* sprite;


void InitScene()
{
	bg = new Background(L"../_Shaders/008_Sprite.fx");

	player = new Player(D3DXVECTOR2(100, 170), D3DXVECTOR2(2.5f, 2.5f));

	sprite = new Sprite(Textures + L"Mario/Single.png", Shaders + L"009_Sprite.fx");
	sprite->Position(300, 170);
	sprite->Scale(100, 100);

}

void DestroyScene()
{
	SAFE_DELETE(sprite);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
}

D3DXMATRIX V, P;
void Update()
{
	
	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	bg->Update(V, P);
	player->Update(V, P);

	D3DXVECTOR3 rotation = sprite->RotationDegree();
	if (Key->Press(VK_LEFT))
		rotation.y -= 40.0f * Timer->Elapsed();
	else if (Key->Press(VK_RIGHT))
		rotation.y += 40.0f * Timer->Elapsed();
	sprite->RotationDegree(rotation);

	//sprite->Rotation(0, sinf(Timer->Running()) * Math::PI, 0);

	sprite->Update(V, P);
}

int pass = 0;
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		bg->Render();
		player->Render();
		sprite->Render();
		
	}
	ImGui::Render();
	SwapChain->Present(0, 0);

}
