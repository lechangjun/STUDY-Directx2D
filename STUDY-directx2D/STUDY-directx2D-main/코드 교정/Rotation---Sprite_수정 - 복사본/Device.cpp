WPARAM Running(HINSTANCE hInstance)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
 
	Key = new Keyboard();
 
	ImGui::Create(Hwnd, Device, DeviceContext);	// ImGui 생성
	ImGui::StyleColorsDark();			// ImGui 색상
 
	Time::Create();
	Time::Get()->Start();
 
	InitScene();
 
	while (true)
	{
		// PeekMessage는 메세지큐에 메세지가 들어와 있는지만을 검사하고 바로 리턴하는 함수
		// PM_REMOVE : 메세지가 있을경우 GetMessage()와 같이 행동, 없을경우 바로 리턴 (PeekMessage : 게임에 적합)
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
 
			TranslateMessage(&msg);	// 해석
			DispatchMessage(&msg);	// 보고
		}
		else
		{
			Time::Get()->Update();
			Update();	// 여기서 처리 (Main.cpp의 Update())
			ImGui::Update();
			Render();	// DeviceContext에서 가져온 정보를 Render에 뿌려줌 (Main.cpp 의 Render())
		}
	}
 
	////////////////////////////////////////
 
	delete Key;
	ImGui::Delete();
	Time::Delete();
 
	UnregisterClass(Title.c_str(), hInstance);
	DestroyWindow(Hwnd);
	DestroyScene();		// Main.cpp
 
	return msg.wParam;
}