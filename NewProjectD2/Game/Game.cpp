#include "framework.h"
#include "Game.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

IDirect3D9*         g_pD3D      = nullptr;
IDirect3DDevice9*   g_pDevice   = nullptr;
int                 someInt     = 10;

bool InitDirect3D(HWND hWnd)
{
    g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!g_pD3D)
    {
        MessageBoxA(hWnd, "Direct3DCreate9 Failed!", "Error", MB_OK);
        return false;
    }

    // 디바이스 생성에 필요한 구조체
    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.BackBufferWidth = 800;   // 임시 값
    d3dpp.BackBufferHeight = 600;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.Windowed = TRUE;  // 창모드
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;

    HRESULT hr = g_pD3D->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &g_pDevice
    );
    if (FAILED(hr))
    {
        MessageBoxA(hWnd, "CreateDevice Failed!", "Error", MB_OK);
        return false;
    }
    return true;
}

void CleanupDirect3D()
{
    if (g_pDevice)
    {
        g_pDevice->Release();
        g_pDevice = nullptr;
    }
    if (g_pD3D)
    {
        g_pD3D->Release();
        g_pD3D = nullptr;
    }
}

bool InitAntTweakBar(HWND hwnd)
{
	if (!TwInit(TW_DIRECT3D9, g_pDevice))
	{
		MessageBoxA(hwnd, "AntTweakBar Init Failed!", "Error", MB_OK);
		return false;
	}

	TwBar* bar = TwNewBar("TestBar");
    TwAddVarRW(bar, "TestVar", TW_TYPE_INT32, &someInt, "label='Test Variable'");

	return true;
}

/// <summary>
/// 프로그램 진입점
/// </summary>
int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
	        if (msg.message == WM_QUIT)
                break;

	        if (TwEventWin(msg.hwnd, msg.message, msg.wParam, msg.lParam))
				continue;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
	        if (g_pDevice)
	        {
				g_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
				if (SUCCEEDED(g_pDevice->BeginScene()))
				{
                    TwDraw();
                    g_pDevice->EndScene();
				}
				g_pDevice->Present(nullptr, nullptr, nullptr, nullptr);
	        }
        }
    }

    TwTerminate();
	CleanupDirect3D();

    return static_cast<int>(msg.wParam);
}

/// <summary>
/// 창 클래스를 등록합니다.
/// </summary>
/// <param name="hInstance"></param>
/// <returns></returns>
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   if (!InitDirect3D(hWnd))
	   return FALSE;

   if (!InitAntTweakBar(hWnd))
	   return FALSE;

   return TRUE;
}

/// <summary>
/// 주 창의 메시지를 처리합니다.
/// </summary>
/// <param name="hWnd"></param>
/// <param name="message"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <remarks>WM_COMMAND - 애플리케이션 메뉴를 처리합니다.</remarks>
/// <remarks>WM_PAINT   - 주 창을 그립니다.</remarks>
/// <remarks>WM_DESTROY - 종료 메시지를 게시하고 반환합니다.</remarks>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
	    {
		    int width = LOWORD(lParam);
			int height = HIWORD(lParam);

            TwWindowSize(width, height);
	    }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}