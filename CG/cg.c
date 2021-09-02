#include <windows.h>
#include <strsafe.h>
#include "resource.h"

#define IDM_FUNC_DDA 	1
#define IDM_FUNC_BRE	2
#define IDM_FUNC_CIR	3
#define IDM_FUNC_OAVL  	4
#define IDM_FUNC_CLEAN	5


int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
int xc = 0, yc = 0;
int r = 0;
int rx = 0, ry = 0;
BOOL flag = FALSE;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_DDA_Bresenham(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Circle(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_Oval(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc_About(HWND, UINT, WPARAM, LPARAM);
HMENU createOwnMenu(HWND);
void DrawAxis(HDC, RECT);
void DDA(HDC, float, float, float, float);
void Bresenham(HDC, int, int, int, int);
void drawcircle(HDC, int);
void drawoval(HDC, double, double);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{


	static TCHAR szAppName[] = TEXT("Mywindows");//定义窗口类的名字
	HWND hwnd;//窗口的句柄
	MSG msg; //消息结构
	WNDCLASS cg; //窗口类结构


	cg.style = CS_VREDRAW | CS_HREDRAW;
	cg.lpfnWndProc = WndProc; //告诉系统我们窗口的窗口过程，这样dispatchmessage带着消息找操作系统系统就知道该用哪个窗口过程
	cg.cbClsExtra = 0;
	cg.cbWndExtra = 0;
	cg.hInstance = hInstance;
	cg.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	cg.hCursor = LoadCursor(NULL, IDC_ARROW);
	cg.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	cg.lpszMenuName = NULL;
	cg.lpszClassName = szAppName;


	if (!RegisterClass(&cg))
	{
		MessageBox(NULL, TEXT("这个程序需要在 Windows NT 下执行!"), TEXT("Error"), MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("WPX's CG Program"),
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);



	/*CreateWindow之后此时窗口进程已经开始运行了
	但是还没有显示在桌面上*/

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))  //消息循环
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	HMENU hMenu;
	static HINSTANCE hInstance;
	static int cxClient, cyClient;


	switch (message)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		hMenu = createOwnMenu(hwnd);
		SetMenu(hwnd, hMenu);
		DialogBoxA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG4), NULL, DlgProc_About);
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		SetMapMode(hdc, MM_LOMETRIC);
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  //设置（0，0）在中心
		DPtoLP(hdc, (PPOINT)& rect, 2); //设备坐标转换成逻辑坐标

		DrawAxis(hdc, rect);	//画坐标轴

		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND: //绑定菜单功能
		hMenu = GetMenu(hwnd);
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		SetMapMode(hdc, MM_LOMETRIC);
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  //设置（0，0）在中心
		DPtoLP(hdc, (PPOINT)&rect, 2); //设备坐标转换成逻辑坐标
		flag = FALSE;
		switch (LOWORD(wParam))
		{
		case IDM_FUNC_DDA:
			DialogBoxA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), NULL, DlgProc_DDA_Bresenham);
			if (flag)
				DDA(hdc, x1, y1, x2, y2);
			return 0;

		case IDM_FUNC_BRE:
			DialogBoxA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), NULL, DlgProc_DDA_Bresenham);
			if (flag)
				Bresenham(hdc, x1, y1, x2, y2);
			return 0;

		case IDM_FUNC_CIR:
			DialogBoxA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG2), NULL, DlgProc_Circle);
			if (flag)
			{
				if (r >= 0)
					drawcircle(hdc, r);
				else
					MessageBox(NULL, TEXT("半径必须为非负数"), TEXT("错误"), MB_ICONERROR | MB_OK);
			}
			return 0;

		case IDM_FUNC_OAVL:
			DialogBoxA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG3), NULL, DlgProc_Oval);
			if (flag)
			{
				if (rx >= 0 && ry >= 0)
					drawoval(hdc, rx, ry);
				else
					MessageBox(NULL, TEXT("横纵半径必须为非负数"), TEXT("错误"), MB_ICONERROR | MB_OK);
			}
			return 0;


		case IDM_FUNC_CLEAN:
			GetClientRect(hwnd, &rect);     //获取客户区大小
			InvalidateRect(hwnd, &rect, TRUE);  //重绘客户区
			return 0;
		}
		ReleaseDC(hwnd, hdc);

	case WM_CLOSE:
		if (MessageBox(NULL, TEXT("确定要关掉我吗？"), TEXT("请确认"), MB_ICONWARNING | MB_YESNO) == IDYES)
			DestroyWindow(hwnd);
		else
			return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

/*创建菜单*/
HMENU createOwnMenu(HWND hwnd)
{
	HMENU hMenu = CreateMenu();
	HMENU hPopMenu = CreateMenu();
	
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_DDA, TEXT("&DDA算法"));
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_BRE, TEXT("&Bresenham算法"));
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_CIR, TEXT("&中点圆算法"));
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_OAVL, TEXT("&中点椭圆算法"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hPopMenu, TEXT("画图"));

	AppendMenu(hMenu, MF_STRING, IDM_FUNC_CLEAN, TEXT("&清除"));

	return hMenu;
}

/*DDA&Bresenham对话框*/
BOOL CALLBACK DlgProc_DDA_Bresenham(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			x1 = GetDlgItemInt(hDlg,IDC_EDIT1, NULL, TRUE);
			y1 = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, TRUE);
			x2 = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, TRUE);
			y2 = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, TRUE);
			flag = TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

/*画圆对话框*/
BOOL CALLBACK DlgProc_Circle(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			xc = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
			yc = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, TRUE);
			r = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, TRUE);
			flag = TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

/*画椭圆对话框*/
BOOL CALLBACK DlgProc_Oval(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			rx = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
			ry = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, TRUE);
			xc = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, TRUE);
			yc = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, TRUE);
			flag = TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

/*版权声明*/
BOOL CALLBACK DlgProc_About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}