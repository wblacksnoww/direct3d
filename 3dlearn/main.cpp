#include <d3d9.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"d3dx9.lib")

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define WINDOW_TITLE	L"aaa"
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;

LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT				Direct3D_Init(HWND hwnd);
HRESULT				Objects_Init(HWND hwnd);
VOID				Direct3D_Render(HWND hwnd);
VOID				Direct3D_CleanUp();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize			= sizeof(WNDCLASSEX);
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= L"ForTheDreamOfGameDevelop";

	if (!RegisterClassEx(&wndClass))
		return -1;

	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE,				//喜闻乐见的创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	Direct3D_Init(hwnd);

	MoveWindow(hwnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	PlaySound(L"War3XMainScreen.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	MessageBox(hwnd, L"gogogo", L"窗口", 0);

	MSG msg = { 0 };
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else
		{
			Direct3D_Render(hwnd);
		}
	}

	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);
	return 0;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_PAINT:
		Direct3D_Render(hwnd);
		ValidateRect(hwnd, NULL);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	case	WM_DESTROY:
		Direct3D_CleanUp();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;

}

HRESULT Direct3D_Init(HWND hwnd)
{
	LPDIRECT3D9 pD3D = NULL;
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
	D3DCAPS9 caps; int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,vp,&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	SAFE_RELEASE(pD3D)

	if (!(S_OK == Objects_Init(hwnd))) return E_FAIL;
	return S_OK;
}

HRESULT Objects_Init(HWND hwnd)
{
	return S_OK;
}

void Direct3D_Render(HWND hwnd)
{

}

void Direct3D_CleanUp()
{

}