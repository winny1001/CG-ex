#include<stdio.h>
#include<windows.h>
extern float x1, x2, y1, y2;

void DDA(HDC hdc, float x1, float y1, float x2, float y2)
{
	float dx, dy;
	float m;



	dx = x1 - x2;
	dy = y1 - y2;
	m = dy / dx;

	SetPixelV(hdc, (int)x1, (int)y1, RGB(255, 0, 0));

	if ((int)x1 == (int)x2)
	{
		while ((int)y1 < (int)y2)
		{
			y1++;
			SetPixelV(hdc, (int)x1, (int)y1, RGB(255, 0, 0));
			Sleep(5);
		}
		while ((int)y1 > (int)y2)
		{
			y1--;
			SetPixelV(hdc, (int)x1, (int)y1, RGB(255, 0, 0));
			Sleep(5);
		}
	}

	if ((int)x1 != (int)x2)
	{
		if (m <= 1)
		{
			while ((int)x1 < (int)x2)
			{
				x1++;
				y1 += m;
				SetPixelV(hdc, (int)x1, (int)(y1 + 0.5), RGB(255, 0, 0));
				Sleep(5);
			}
			while ((int)x1 > (int)x2)
			{
				x1--;
				y1 -= m;
				SetPixelV(hdc, (int)x1, (int)(y1 + 0.5), RGB(255, 0, 0));
				Sleep(5);
			}
		}
		if (m > 1)
		{
			while ((int)y1 < (int)y2)
			{
				y1++;
				x1 += 1 / m;
				SetPixelV(hdc, (int)(x1 + 0.5), (int)y1, RGB(255, 0, 0));
				Sleep(5);
			}
			while ((int)y1 > (int)y2)
			{
				y1--;
				x1 -= 1 / m;
				SetPixelV(hdc, (int)(x1 + 0.5), (int)y1, RGB(255, 0, 0));
				Sleep(5);
			}
		}
		
	}

}