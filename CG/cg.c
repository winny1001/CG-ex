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


	static TCHAR szAppName[] = TEXT("Mywindows");//���崰���������
	HWND hwnd;//���ڵľ��
	MSG msg; //��Ϣ�ṹ
	WNDCLASS cg; //������ṹ


	cg.style = CS_VREDRAW | CS_HREDRAW;
	cg.lpfnWndProc = WndProc; //����ϵͳ���Ǵ��ڵĴ��ڹ��̣�����dispatchmessage������Ϣ�Ҳ���ϵͳϵͳ��֪�������ĸ����ڹ���
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
		MessageBox(NULL, TEXT("���������Ҫ�� Windows NT ��ִ��!"), TEXT("Error"), MB_ICONERROR);
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



	/*CreateWindow֮���ʱ���ڽ����Ѿ���ʼ������
	���ǻ�û����ʾ��������*/

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))  //��Ϣѭ��
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
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  //���ã�0��0��������
		DPtoLP(hdc, (PPOINT)& rect, 2); //�豸����ת�����߼�����

		DrawAxis(hdc, rect);	//��������

		EndPaint(hwnd, &ps);
		return 0;

	case WM_COMMAND: //�󶨲˵�����
		hMenu = GetMenu(hwnd);
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		SetMapMode(hdc, MM_LOMETRIC);
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);  //���ã�0��0��������
		DPtoLP(hdc, (PPOINT)&rect, 2); //�豸����ת�����߼�����
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
					MessageBox(NULL, TEXT("�뾶����Ϊ�Ǹ���"), TEXT("����"), MB_ICONERROR | MB_OK);
			}
			return 0;

		case IDM_FUNC_OAVL:
			DialogBoxA(hInstance, MAKEINTRESOURCEA(IDD_DIALOG3), NULL, DlgProc_Oval);
			if (flag)
			{
				if (rx >= 0 && ry >= 0)
					drawoval(hdc, rx, ry);
				else
					MessageBox(NULL, TEXT("���ݰ뾶����Ϊ�Ǹ���"), TEXT("����"), MB_ICONERROR | MB_OK);
			}
			return 0;


		case IDM_FUNC_CLEAN:
			GetClientRect(hwnd, &rect);     //��ȡ�ͻ�����С
			InvalidateRect(hwnd, &rect, TRUE);  //�ػ�ͻ���
			return 0;
		}
		ReleaseDC(hwnd, hdc);

	case WM_CLOSE:
		if (MessageBox(NULL, TEXT("ȷ��Ҫ�ص�����"), TEXT("��ȷ��"), MB_ICONWARNING | MB_YESNO) == IDYES)
			DestroyWindow(hwnd);
		else
			return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

/*�����˵�*/
HMENU createOwnMenu(HWND hwnd)
{
	HMENU hMenu = CreateMenu();
	HMENU hPopMenu = CreateMenu();
	
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_DDA, TEXT("&DDA�㷨"));
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_BRE, TEXT("&Bresenham�㷨"));
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_CIR, TEXT("&�е�Բ�㷨"));
	AppendMenu(hPopMenu, MF_STRING, IDM_FUNC_OAVL, TEXT("&�е���Բ�㷨"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hPopMenu, TEXT("��ͼ"));

	AppendMenu(hMenu, MF_STRING, IDM_FUNC_CLEAN, TEXT("&���"));

	return hMenu;
}

/*DDA&Bresenham�Ի���*/
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

/*��Բ�Ի���*/
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

/*����Բ�Ի���*/
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

/*��Ȩ����*/
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