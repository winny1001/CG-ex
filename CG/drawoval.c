#include<windows.h>

extern double rx, ry;
extern int xc, yc;

static void print_point(HDC hdc, int x, int y)
{
	SetPixelV(hdc, (int)(x + 0.5) + xc, (int)(y + 0.5) + yc, RGB(255, 0, 0));
	SetPixelV(hdc, -(int)(x + 0.5) + xc, (int)(y + 0.5) + yc, RGB(255, 0, 0));
	SetPixelV(hdc, (int)(x + 0.5) + xc, -(int)(y + 0.5) + yc, RGB(255, 0, 0));
	SetPixelV(hdc, -(int)(x + 0.5) + xc, -(int)(y + 0.5) + yc, RGB(255, 0, 0));
}

void drawoval(HDC hdc,double rx, double ry)
{
	double x, y;
	double p1, p2;
	double ry2;
	double rx2;

	
	x = 0;
	y = ry;
	ry2 = ry * ry;
	rx2 = rx * rx;

	SetPixelV(hdc, xc, yc, RGB(255, 0, 0));	//ÖÐÐÄ
	print_point(hdc, x, y);
	
	p1 = ry2 - rx2 * ry + 0.25 * rx2;

	while (ry2 * x < rx2 * y)
	{
		if (p1 < 0)
		{
			x++;
			p1 += 2 * ry2 * x + ry2;
			print_point(hdc, x, y);
			Sleep(10);
		}
		else
		{
			x++;
			y--;
			p1 += 2 * ry2 * x - 2 * rx2 * y + ry2;
			print_point(hdc, x, y);
			Sleep(10);
		}
	}

	p2 = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;

	while (rx2 * y <= ry2 * x && x && y)
	{
		if (p2 > 0)
		{
			y--;
			p2 += -2 * rx2 * y + rx2;
			print_point(hdc, x, y);
			Sleep(10);
		}
		else
		{
			y--;
			x++;
			p2 += 2 * ry2 * x - 2 * rx2 * y + rx2;
			print_point(hdc, x, y);
			Sleep(10);
		}
	}
}