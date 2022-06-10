/***************************************************
 <EternityEngine>

 DirectX12ベースにしようと思ったのですが
 時間的に作品展に間に合わない可能性があるので
 DirectX11ベースにしました。
****************************************************/

#include "./Application/Application.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dCompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"DirectXTex.lib")

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "DirectXTK_d.lib")
#else
#pragma comment(lib, "DirectXTK.lib")
#endif

int CALLBACK WinMain( HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	Eternity::Application::CApplication mainSystem;
	mainSystem.Initialize("Game", 1280, 720, true);
	mainSystem.MainLoop();
	return 0;
}