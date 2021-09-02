#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
extern float x1, x2, y1, y2;

//坐标交换
void exchange(int *x1, int *y1, int *x2, int *y2)
{
	int temp;
	temp = *x1;
	*x1 = *x2;
	*x2 = temp;
	temp = *y1;
	*y1 = *y2;
	*y2 = temp;
} 


void Bresenham(HDC hdc, int x1, int y1, int x2, int y2)
{	
	int dx, dy;
	int p;
	int d2y, d2x, d2yx, d2xy;


	dx = abs(x1 - x2);
	dy = abs(y1 - y2);
	d2y = 2 * dy;
	d2x = 2 * dx;
	d2xy = d2x - d2y;
	d2yx = d2y - d2x;

	//画垂直x轴直线
	if (x1 == x2)
	{
		printf("(%d,%d)", x1, y1);
		while (y1 != y2)
		{
			if (y1 > y2)
				y1--;
			if (y1 < y2)
				y1++;
			SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
			Sleep(5);
		}
	}

	//画斜线（包括平行于x轴）
	if(x1 != x2)
	{
		//当 |m| < 1 时
		if (dy / dx <= 1)
		{
			//确保从左向右画
			if (x1 > x2)
				exchange(&x1, &y1, &x2, &y2);

			SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
			p = d2y - dx;

			while (x1 != x2 || y1 != y2)
			{
				if (p < 0)
				{
					x1++;
					p += d2y;
					SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
					Sleep(5);
					continue;
				}
				if (p >= 0)
				{
					x1++;
					if (y1 > y2)
						y1--;
					if (y1 < y2)
						y1++;
					p += d2yx;
					SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
					Sleep(5);
					continue;
				}
			}
		}

		//当 |m| > 1 时
		if (dy / dx > 1)
		{
			if (y1 > y2)
				exchange(&x1, &y1, &x2, &y2);

			SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
			p = d2x - dy;

			while (x1 != x2 || y1 != y2)  
			{
				if (p < 0)
				{
					y1++;
					p += d2x;
					SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
					Sleep(5);
					continue;
				}
				if (p >= 0)
				{
					y1++;
					if (x1 > x2)
						x1--;
					if (x1 < x2)
						x1++;
					p += d2xy;
					SetPixelV(hdc, x1, y1, RGB(255, 0, 0));
					Sleep(5);
					continue;
				}
			}
		}

	}
}

