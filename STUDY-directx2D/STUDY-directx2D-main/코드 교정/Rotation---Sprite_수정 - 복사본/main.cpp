#include "stdafx.h"
#include "./System/Device.h"
#include "./Render/Rect.h"
#include "./Object/Bullet.h"

Sprite* mario;
Sprite* allMario;

vector<Bullet*> bullets;
D3DXVECTOR2 position;	// 총알 시작 위치

D3DXMATRIX V, P;	// 3D물체를 모니터에 그리기 위해 3D 공간변환을 하기 위한 행렬


void InitScene()
{
	wstring shaderFile = L"./_Shader2D/Effect.fx";

	mario = new Sprite(L"./_Textures/mario.png", shaderFile);
	mario->Position(100, 100);

	allMario = new Sprite(L"./_Textures/spriteMario.png", shaderFile, 10, 87, 50, 160);
	allMario->Position(300.0f, 140.0f);

	position = D3DXVECTOR2(300.0f, 140.0f);
}


void DestroyScene()
{
	SAFE_DELETE(allMario);
	SAFE_DELETE(mario);
}

void Update()
{
	// D3DXMatrixIdentity : 일단 항등행렬로 만들어줌
	D3DXMatrixIdentity(&V);
	D3DXMatrixIdentity(&P);

	// View
	// 아래의 3가지 정보만 있으면 D3DXMatrixLookAtLH() 함수를 호출하여 뷰행렬을 만들 수 있다.
	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);		// 카메라가 보는 위치
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);		// 바라보는 곳의 위치
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);		// 카메라의 위를 가리키는 벡터

	D3DXMatrixLookAtLH(&V, &eye, &at, &up);	// 뷰 행렬 만들기

	// Projection(투영)
	//연산 결과 Matrix ,x최소, x 최대, y최소, y최대, z최소, z최대 (볼륨 값의 최대 최소) 
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	mario->Update(V, P);
	allMario->Update(V, P);

	if (Key->Press('A'))
	{
		position.x -= 200.0f * Time::Delta();
		allMario->Position(position);
	}
	else if (Key->Press('D'))
	{
		position.x += 200.0f * Time::Delta();
		allMario->Position(position);
	}
	else if (Key->Press('W'))
	{
		position.y += 200.0f * Time::Delta();
		allMario->Position(position);
	}
	else if (Key->Press('S'))
	{
		position.y -= 200.0f * Time::Delta();
		allMario->Position(position);
	}

	if (Key->Press(VK_SPACE))	// 스페이스바
	{
		wstring textureFile = L"./_Textures/bullet.png";
		wstring shaderFile = L"./_Shader2D/Effect.fx";
		float angle = Math::Random(-179.9f, 179.9f);
		float speed = Math::Random(0.5f, 1.0f);
		Bullet* bullet = new Bullet(textureFile, shaderFile, position, angle, speed);

		bullets.push_back(bullet);
	}

	for (Bullet* bullet : bullets)
	{
		bullet->Update(V, P);
	}
}

void Render()
{
	// D3DXCOLOR
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		// 그려줄 코드 작성
		mario->Render();
		allMario->Render();

		for (Bullet* bullet : bullets)
		{
			bullet->Render();
		}
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}