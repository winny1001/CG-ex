#include<Windows.h>
#include<strsafe.h>

void DrawAxis(HDC hdc, RECT rect)
{
	size_t iTarget;
	TCHAR szbuffer[128];
	int x, y;

	/*��x��*/
	MoveToEx(hdc, rect.left, 0, NULL);
	LineTo(hdc, rect.right, 0);
	/*��y��*/
	MoveToEx(hdc, 0, rect.top, NULL);
	LineTo(hdc, 0, rect.bottom);
	/*��x��̶���*/
	for (x = 0; x <= rect.right; x += 50)
	{
		MoveToEx(hdc, x, -5, NULL);
		LineTo(hdc, x, 5);
		MoveToEx(hdc, -x, -5, NULL);
		LineTo(hdc, -x, 5);
	}
	/*��y��̶���*/
	for (y = 0; y <= rect.top; y += 50)
	{
		MoveToEx(hdc, -5, y, NULL);
		LineTo(hdc, 5, y);
		MoveToEx(hdc, -5, -y, NULL);
		LineTo(hdc, 5, -y);
	}

	/*��ԭ��*/
	TextOut(hdc, 10, -10, TEXT("0"), 1);
	/*��x��̶ȱ�ʶ*/
	for (x = 100; x <= rect.right; x += 100)
	{
		StringCchPrintf(szbuffer, 128, TEXT("%d"), x);
		StringCchLength(szbuffer, 128, &iTarget);
		TextOut(hdc, x, -10, szbuffer, iTarget);
		StringCchPrintf(szbuffer, 128, TEXT("-%d"), x);
		TextOut(hdc, -x, -10, szbuffer, iTarget + 1);
	}

	/*��y��̶ȱ�ʶ*/
	for (y = 100; y <= rect.right; y += 100)
	{
		StringCchPrintf(szbuffer, 128, TEXT("%d"), y);
		StringCchLength(szbuffer, 128, &iTarget);
		TextOut(hdc, 10, y, szbuffer, iTarget);
		StringCchPrintf(szbuffer, 128, TEXT("-%d"), y);
		TextOut(hdc, 10, -y, szbuffer, iTarget + 1);
	}

}