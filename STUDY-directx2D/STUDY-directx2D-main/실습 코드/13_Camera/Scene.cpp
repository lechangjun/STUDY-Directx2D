#include "stdafx.h"
#include "Device.h"
#include "Objects/Background.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"


Background* bg;
Player* player;
Sprite* sprite;
Camera* camera;


void InitScene()
{
	player = new Player(D3DXVECTOR2(500, 140), D3DXVECTOR2(2.5f, 2.5f));
	//camera = new Freedom;
	camera = new Following(player);
	bg = new Background(Shaders + L"009_Sprite.fx");


	sprite = new Sprite(Textures + L"Stage.png", Shaders + L"009_Sprite.fx");
	sprite->Scale(2.5f, 2.5f);
	sprite->Position(0, 300);


}

void DestroyScene()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(sprite);
	SAFE_DELETE(player);
	SAFE_DELETE(bg);
}

void Update()
{
	
	
	D3DXMATRIX P;

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	camera->Update();

	D3DXMATRIX V = camera->View();


	//bg->Update(V, P);
	player->Update(V, P);

	sprite->Update(V, P);

	int a = 10;
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		//bg->Render();
		sprite->Render();
		player->Render();
		
		
	}
	ImGui::Render();
	SwapChain->Present(0, 0);

}
