#include <windows.h>	

extern int xc, yc, r;

static void print_point(HDC hdc,int x, int y)
{
	SetPixelV(hdc, x + xc, y + yc, RGB(255,0,0));
	SetPixelV(hdc, -x + xc, y + yc, RGB(255, 0, 0));
	SetPixelV(hdc, x + xc, -y + yc, RGB(255, 0, 0));
	SetPixelV(hdc, -x + xc, -y + yc, RGB(255, 0, 0));
	SetPixelV(hdc, y + xc, x + yc, RGB(255, 0, 0));
	SetPixelV(hdc, -y + xc, x + yc, RGB(255, 0, 0));
	SetPixelV(hdc, y + xc, -x + yc, RGB(255, 0, 0));
	SetPixelV(hdc, -y + xc, -x + yc, RGB(255, 0, 0));
}

void drawcircle(HDC hdc, int r)
{
	float p;
	int x, y;


	x = 0;
	y = r;

	p = 5 / 4 - r;

	SetPixelV(hdc, xc, yc, RGB(255, 0, 0));	//Ô²ÐÄ
	print_point(hdc, x, y);

	while (x < y)
	{
		if (p < 0)
		{
			x++;
			p += 2 * x + 1;
			print_point(hdc, x, y);
			Sleep(10);
			continue;
		}

		if (p >= 0)
		{
			x++;
			y--;
			p += 2 * x + 1 - 2 * y;
			print_point(hdc, x, y);
			Sleep(10);
			continue;
		}
	}
}