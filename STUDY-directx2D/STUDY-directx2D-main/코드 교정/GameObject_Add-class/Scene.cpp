#include "stdafx.h"
#include "./Systems/Device.h"
#include "./GameObject/RandomShooter.h"
#include "./GameObject/Ground.h"
#include "./GameObject/Trex.h"
#include "./GameObject/Cactus.h"

Trex* character;
vector<RandomShooter*> generators;
vector<Cactus*> cactus;
vector<Cactus*> cloud;
vector<Ground*> grounds;
float speed = 350.0f;
float cloudSpeed = 50.0f;
float score = 0;

void InitScene() {
	wstring spriteFile = Textures + L"Trex/Sprite.png";
	wstring shaderFile = Shaders + L"008_Sprite.fx";
	{
		grounds.push_back(new Ground(shaderFile, Textures + L"Trex/Floor.png", D3DXVECTOR2(0, Height / 2 - 4), &speed));
		grounds.push_back(new Ground(shaderFile, Textures + L"Trex/Floor.png", D3DXVECTOR2(1200, Height / 2 - 4), &speed));
	}

	{
		generators.push_back(new RandomShooter(shaderFile, Textures + L"Trex/Cactus1.png",
			&cactus, &speed, D3DXVECTOR2(17,35),
			D3DXVECTOR2(1,10), D3DXVECTOR2(Width, Height / 2 + 12), D3DXVECTOR2(0,0), D3DXVECTOR2(200,0)));

		generators.push_back(new RandomShooter(shaderFile, Textures + L"Trex/Cactus2.png",
			&cactus, &speed, D3DXVECTOR2(24, 50),
			D3DXVECTOR2(2, 11), D3DXVECTOR2(Width, Height / 2 + 12), D3DXVECTOR2(0, 0), D3DXVECTOR2(200, 0)));

		generators.push_back(new RandomShooter(shaderFile, Textures + L"Trex/Cactus3.png",
			&cactus, &speed, D3DXVECTOR2(29, 47),
			D3DXVECTOR2(3, 12), D3DXVECTOR2(Width, Height / 2 + 12), D3DXVECTOR2(0, 0), D3DXVECTOR2(200, 0)));

		generators.push_back(new RandomShooter(shaderFile, Textures + L"Trex/Cactus4.png",
			&cactus, &speed, D3DXVECTOR2(37, 49),
			D3DXVECTOR2(4, 13), D3DXVECTOR2(Width, Height / 2 + 12), D3DXVECTOR2(0, 0), D3DXVECTOR2(200, 0)));
	}

	{
		generators.push_back(new RandomShooter(shaderFile, spriteFile,
			&cactus, &speed, D3DXVECTOR2(46, 42),
			D3DXVECTOR2(0, 10), D3DXVECTOR2(Width, Height / 2 + 20), D3DXVECTOR2(0, 0), D3DXVECTOR2(200, 100),
			D3DXVECTOR2(134, 0), D3DXVECTOR2(180, 42), D3DXVECTOR2(180, 0), D3DXVECTOR2(226, 42)));
	}

	{
		generators.push_back(new RandomShooter(shaderFile, Textures + L"Trex/Cloud.png",
			&cloud, &cloudSpeed, D3DXVECTOR2(46, 13),
			D3DXVECTOR2(0, 5), D3DXVECTOR2(Width, Height / 2 + 80), D3DXVECTOR2(0, 0), D3DXVECTOR2(200, 100)));
	}

	{
		character = new Trex(shaderFile, spriteFile, D3DXVECTOR2(52, Height / 2 + 12), speed);
	}
}

void DestroyScene() {
	SAFE_DELETE(character);

	for (auto g : grounds)
		SAFE_DELETE(g);

	for (auto g : generators)
		SAFE_DELETE(g);

	for (auto c : cactus)
		SAFE_DELETE(c);
	
	for (auto c : cloud)
		SAFE_DELETE(c);
}

D3DXMATRIX V, P;

void Update() {
	//============================================================================
	// Player Key Input
	if (Key->Down(VK_SPACE))
		character->StartJump();
	else if (Key->Up(VK_SPACE))
		character->EndJump();

	if (Key->Down(VK_DOWN))
		character->StartCrouch();
	else if (Key->Up(VK_DOWN))
		character->EndCrouch();

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	//============================================================================
	// RandomGen Update
	for (auto g : generators)
		g->Update();

	//============================================================================
	// GameObject Update
	for (auto g : grounds) {
		g->Update(V, P);
	}

	for (auto iter = cactus.begin(); iter != cactus.end();) {
		(*iter)->Update(V, P);
		if ((*iter)->trashFlag) {
			delete *iter;
			iter = cactus.erase(iter);
		}
		else {
			iter++;
		}
	}

	for (auto iter = cloud.begin(); iter != cloud.end();) {
		(*iter)->Update(V, P);
		if ((*iter)->trashFlag) {
			delete *iter;
			iter = cloud.erase(iter);
		}
		else {
			iter++;
		}
	}

	character->Update(V, P);

	//============================================================================
	// Score Update
	bool isHit = false;
	for (auto c : cactus) {
		if (character->CollisionCheck(*c))
  			isHit = true;
	}

	if (isHit) {
		speed = 0;
		MessageBox(Hwnd, L"Game Over", L"Game Over", MB_OK);
		exit(0);
	}

	score += speed * Time::Delta();
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(.97f, .97f, .97f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		ImGui::Text("Score: %.0f", score);
		ImGui::SliderFloat("Speed", &speed, 0.0f, 700.0f);
		cloudSpeed = speed / 7;

		for (auto g : grounds) {
			g->Render();
		}
		for (auto c : cloud) {
			c->Render();
		}
		for (auto c : cactus) {
			c->Render();
		}
		character->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}