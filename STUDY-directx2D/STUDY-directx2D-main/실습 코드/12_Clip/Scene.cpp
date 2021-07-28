#include "stdafx.h"
#include "Device.h"
#include "Objects/Background.h"
#include "Objects/Bullet.h"

Background* bg;
Clip* clip;

void InitScene()
{
	bg = new Background(L"../_Shaders/008_Sprite.fx");

	wstring spriteFile = Textures + L"Metalslug.png";
	wstring shaderFile = L"../_Shaders/008_Sprite.fx";

	clip = new Clip(PlayMode::End);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 34, 40), 0.3f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
	clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 94, 40), 0.3f);

	clip->Position(100, 170);
	clip->Scale(2.5f, 2.5f);
	clip->Play();
}

void DestroyScene()
{
	SAFE_DELETE(clip);
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
	clip->Update(V, P);
}

int pass = 0;
void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		bg->Render();
		clip->Render();
		
	}
	ImGui::Render();
	SwapChain->Present(0, 0);

}