#include "stdafx.h"
#include "Device.h"
#include "Draws/Rect.h"
#include "Player.h"

Player* player;

void InitScene()
{
	player = new Player(L"../_Shaders/006_Rect.fx");
	player->Scale(100, 100);

	float x = (float)Width * 0.5f - player->Scale().x * 0.5f;
	float y = player->Scale().y * 0.5f;
	player->Position(x, y);
}

void DestroyScene()
{
	SAFE_DELETE(player);
}

D3DXMATRIX V, P;
void Update()
{
	//Á¡ÇÁ
	if (Key->Press(VK_SPACE))
	{
		player->StartJump();
	}
	else if (Key->Up(VK_SPACE))
	{
		player->EndJump();
	}


	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	player->ViewProjection(V, P);
	player->Update();
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::SliderFloat("Speed", player->pSpeed(), 0.05f, 0.3f);
		if (ImGui::Button("Stop") == true)
		{
			player->Stop();
		}
		if (ImGui::Button("Restart") == true)
		{
			player->Restart();
		}

		player->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}