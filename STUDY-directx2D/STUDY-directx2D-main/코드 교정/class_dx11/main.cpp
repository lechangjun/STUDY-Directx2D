#include "./Render/Rect.h"
 
 
Rect* rect1;
Rect* rect2;
 
D3DXMATRIX V, P;	// W 지움
 
 
void InitScene()
{
	wstring shaderFile = L"./_Shader2D/Effect.fx";
 
	rect1 = new Rect(shaderFile);
	rect1->Position(200, 100);
	rect1->Scale(100, 100);
	rect1->Color(1, 1, 0);
 
	rect2 = new Rect
	(
		shaderFile,
		D3DXVECTOR2(500, 500),
		D3DXVECTOR2(100, 100),
		D3DXCOLOR(1,0,1,1)
	);
 
	D3DXCOLOR sampleColor = D3DXCOLOR(0, 0, 1, 1);
	rect2->Color(sampleColor);
	
}
 
 
void DestroyScene()
{
	SAFE_DELETE(rect1);
	SAFE_DELETE(rect2);
}
 
void Render()
{
	// D3DXCOLOR
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
 
		// 그려줄 코드 작성
		rect->Render();
		rect2->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}