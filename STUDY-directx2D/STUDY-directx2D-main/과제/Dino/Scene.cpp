#include "stdafx.h"
#include "Device.h"
#include "Texture.h"

Texture* Trex; //����

Texture* Map_Floor[2]; //�� �ٴ�(2���� �Ѽ�Ʈ)
Texture* Map_Cloud; //�� ����
Texture* Bird; //��
Texture* Cactus[4]; //������(4����)

int Random_Cactus = -1;//������ ��� ����

bool bCactus1 = false; //1�� ������
bool bCactus2 = false; //2��
bool bCactus3 = false; //3��
bool bCactus4 = false; //4��

void InitScene()
{
	//����
	Trex = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Trex.png",
		D3DXVECTOR2(100, 134),
		D3DXVECTOR2(80, 80)
	);

	//�ٴ� 1��
	Map_Floor[0] = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Floor.png",
		D3DXVECTOR2(Width / 2, 100),
		D3DXVECTOR2(Width, 20)
	);
	Map_Floor[0]->Speed(200); //�ٴ� �ӵ�
	//�ٴ� 2��
	Map_Floor[1] = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Floor.png",
		D3DXVECTOR2(Width / 2 + Width, 100),
		D3DXVECTOR2(Width, 20)
	);
	Map_Floor[1]->Speed(200);

	//�� ����
	Map_Cloud = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Cloud.png",
		D3DXVECTOR2(Math::Random((int)Width + 30, (int)Width * 2 + 30), 500),
		D3DXVECTOR2(120, 40)
	);
	Map_Cloud->Speed(Math::Random(100, 400)); //���� �ӵ�

	//��
	Bird = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Bird.png",
		D3DXVECTOR2(Math::Random((int)Width + 30, (int)Width * 2 + 30), Math::Random(264, 462)),
		D3DXVECTOR2(60, 50)
	);
	Bird->Speed(Math::Random(150, 400));

	//������
	Cactus[0] = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Cactus1.png",
		D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134),
		D3DXVECTOR2(50, 100)
	);
	Cactus[0]->Speed(200); //������ �ӵ�(�ٴ��̶� �Ȱ���)
	Cactus[1] = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Cactus2.png",
		D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134),
		D3DXVECTOR2(50, 100)
	);
	Cactus[1]->Speed(200);
	Cactus[2] = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Cactus3.png",
		D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134),
		D3DXVECTOR2(50, 100)
	);
	Cactus[2]->Speed(200);
	Cactus[3] = new Texture
	(
		L"../_Shaders/007_Texture.fx",
		L"../_Textures/Cactus4.png",
		D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134),
		D3DXVECTOR2(50, 100)
	);
	Cactus[3]->Speed(200);

	//������ ���� ����
	Random_Cactus = Math::Random(0, 3);
	switch (Random_Cactus)
	{
	case 0:
		//Cactus[0]->Go_Left();
		bCactus1 = true;
		break;
	case 1:
		//Cactus[1]->Go_Left();
		bCactus2 = true;
		break;
	case 2:
		//Cactus[2]->Go_Left();
		bCactus3 = true;
		break;
	case 3:
		//Cactus[3]->Go_Left();
		bCactus4 = true;
		break;
	}
}

void DestroyScene()
{
	SAFE_DELETE(Trex);
	for (int i = 0; i < 2; i++)
		SAFE_DELETE(Map_Floor[i]);
	SAFE_DELETE(Map_Cloud);
	SAFE_DELETE(Bird);
	for (int i = 0; i < 4; i++)
		SAFE_DELETE(Cactus[i]);
}

D3DXMATRIX V, P;
void Update()
{
	//<<������ �̵�
	Map_Floor[0]->Go_Left();
	Map_Floor[1]->Go_Left();
	Map_Cloud->Go_Left();
	Bird->Go_Left();

	if (bCactus1 == true)
	{
		Cactus[0]->Go_Left();
	}
	if (bCactus2 == true)
	{
		Cactus[1]->Go_Left();
	}
	if (bCactus3 == true)
	{
		Cactus[2]->Go_Left();
	}
	if (bCactus4 == true)
	{
		Cactus[3]->Go_Left();
	}

	//ȭ�� ������ ����� �͵� ��ġ ������
	//����
	if (Map_Cloud->Position().x + Map_Cloud->Scale().x / 2 <= 0)
	{
		Map_Cloud->Position(D3DXVECTOR2(Math::Random((int)Width + 30, (int)Width * 2 + 30), 500));
		Map_Cloud->Speed(Math::Random(100, 400));
	}
	//��
	if (Bird->Position().x + Bird->Scale().x / 2 <= 0)
	{
		Bird->Position(D3DXVECTOR2(Math::Random((int)Width + 30, (int)Width * 2 + 30), Math::Random(264, 462)));
		Bird->Speed(Math::Random(150, 400));
	}
	//������
	if (Cactus[0]->Position().x + Cactus[0]->Scale().x <= 0)
	{
		Cactus[0]->Position(D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134));
		Cactus[0]->Speed(200);
	}
	if (Cactus[1]->Position().x + Cactus[1]->Scale().x <= 0)
	{
		Cactus[1]->Position(D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134));
		Cactus[1]->Speed(200);
	}
	if (Cactus[2]->Position().x + Cactus[2]->Scale().x <= 0)
	{
		Cactus[2]->Position(D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134));
		Cactus[2]->Speed(200);
	}
	if (Cactus[3]->Position().x + Cactus[3]->Scale().x <= 0)
	{
		Cactus[3]->Position(D3DXVECTOR2(Math::Random((float)Width + 25, (float)Width * 2 - 25), 134));
		Cactus[3]->Speed(200);
	}

	//���� �浹
	for (int i = 0; i < 4; i++)
	{
		if (Trex->Position().x + Trex->Scale().x / 2 >= Bird->Position().x - Bird->Scale().x / 2 &&
			Trex->Position().x - Trex->Scale().x / 2 <= Bird->Position().x + Bird->Scale().x / 2 &&
			Trex->Position().y + Trex->Scale().y / 2 >= Bird->Position().y - Bird->Scale().y / 2 &&
			Trex->Position().y - Trex->Scale().y / 2 <= Bird->Position().y + Bird->Scale().y / 2)
		{
			MessageBox(Hwnd, L"Game Over", L"Game Over!", MB_OK);

			//�ٴ��ʱ�ȭ
			Map_Floor[0]->Position(D3DXVECTOR2(Width / 2, 100));
			Map_Floor[1]->Position(D3DXVECTOR2(Width / 2 + Width, 100));
		}
	}
	//������� �浹
	for (int i = 0; i < 4; i++)
	{
		if (Trex->Position().x + Trex->Scale().x / 2 >= Cactus[i]->Position().x - Cactus[i]->Scale().x / 2 &&
			Trex->Position().x - Trex->Scale().x / 2 <= Cactus[i]->Position().x + Cactus[i]->Scale().x / 2 &&
			Trex->Position().y + Trex->Scale().y / 2 >= Cactus[i]->Position().y - Cactus[i]->Scale().y / 2 &&
			Trex->Position().y - Trex->Scale().y / 2 <= Cactus[i]->Position().y + Cactus[i]->Scale().y / 2)
		{
			MessageBox(Hwnd, L"Game Over", L"Game Over!", MB_OK);

			//�ٴ��ʱ�ȭ
			Map_Floor[0]->Position(D3DXVECTOR2(Width / 2, 100));
			Map_Floor[1]->Position(D3DXVECTOR2(Width / 2 + Width, 100));
		}
	}

	//�ٴڼ���
	D3DXVECTOR2 setFloor = D3DXVECTOR2(Width / 2 + Width, 100);

	if (Map_Floor[0]->Position().x + Map_Floor[0]->Scale().x / 2 <= 0)
	{
		Map_Floor[0]->Position(setFloor);
		Random_Cactus = Math::Random(0, 3);
		switch (Random_Cactus)
		{
		case 0:
			bCactus1 = true;
			break;
		case 1:
			bCactus2 = true;
			break;
		case 2:
			bCactus3 = true;
			break;
		case 3:
			bCactus4 = true;
			break;
		}
	}
	if (Map_Floor[1]->Position().x + Map_Floor[1]->Scale().x / 2 <= 0)
	{
		Map_Floor[1]->Position(setFloor);
		Random_Cactus = Math::Random(0, 3);
		switch (Random_Cactus)
		{
		case 0:
			bCactus1 = true;
			break;
		case 1:
			bCactus2 = true;
			break;
		case 2:
			bCactus3 = true;
			break;
		case 3:
			bCactus4 = true;
			break;
		}
	}

	//����
	if (Key->Down(VK_SPACE))
		Trex->StartJump();
	else if (Key->Up(VK_SPACE))
		Trex->EndJump();

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Prjection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	Trex->ViewProjection(V, P);
	Trex->Update();

	Map_Floor[0]->ViewProjection(V, P);
	Map_Floor[0]->Update();

	Map_Floor[1]->ViewProjection(V, P);
	Map_Floor[1]->Update();

	Map_Cloud->ViewProjection(V, P);
	Map_Cloud->Update();

	Bird->ViewProjection(V, P);
	Bird->Update();

	Cactus[0]->ViewProjection(V, P);
	Cactus[0]->Update();

	Cactus[1]->ViewProjection(V, P);
	Cactus[1]->Update();

	Cactus[2]->ViewProjection(V, P);
	Cactus[2]->Update();

	Cactus[3]->ViewProjection(V, P);
	Cactus[3]->Update();
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		Trex->Render();

		Map_Floor[0]->Render();
		Map_Floor[1]->Render();

		Map_Cloud->Render();

		Bird->Render();

		Cactus[0]->Render();
		Cactus[1]->Render();
		Cactus[2]->Render();
		Cactus[3]->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}