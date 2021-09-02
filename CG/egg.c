#include<Windows.h>	

void egg(HDC hdc, PAINTSTRUCT ps, int cxClient, int cyClient)
{
	HPEN hPen, hOldPen;
	HBRUSH hBlueBrush, hOldBrush, hRedBrush, hYellowBrush;
	POINT apt[128];

	hPen = CreatePen(PS_DOT, 1, RGB(192, 192, 192));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, cxClient / 2, 0, NULL);
	LineTo(hdc, cxClient / 2, cyClient);
	MoveToEx(hdc, 0, cyClient / 2, NULL);
	LineTo(hdc, cxClient, cyClient / 2);
	SelectObject(hdc, hOldPen);

	//ͷ ֱ��240
	hBlueBrush = CreateSolidBrush(RGB(0, 159, 232));	//��
	hOldBrush = SelectObject(hdc, hBlueBrush);
	Ellipse(hdc, cxClient / 2 - 120, cyClient / 2 - 200, cxClient / 2 + 120, cyClient / 2 + 40);
	SelectObject(hdc, hOldBrush);	//��

	//�� ֱ��200 
	Ellipse(hdc, cxClient / 2 - 100, cyClient / 2 - 160, cxClient / 2 + 100, cyClient / 2 + 40);

	//�۾� ��60 ��50 
	Ellipse(hdc, cxClient / 2 - 50, cyClient / 2 - 180, cxClient / 2, cyClient / 2 - 120);
	Ellipse(hdc, cxClient / 2 + 50, cyClient / 2 - 180, cxClient / 2, cyClient / 2 - 120);

	//���� 
	hOldBrush = SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Ellipse(hdc, cxClient / 2 - 20, cyClient / 2 - 160, cxClient / 2 - 5, cyClient / 2 - 140);
	Ellipse(hdc, cxClient / 2 + 20, cyClient / 2 - 160, cxClient / 2 + 5, cyClient / 2 - 140);
	SelectObject(hdc, hOldBrush);
	hOldBrush = SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Ellipse(hdc, cxClient / 2 - 15, cyClient / 2 - 155, cxClient / 2 - 10, cyClient / 2 - 145);
	Ellipse(hdc, cxClient / 2 + 15, cyClient / 2 - 155, cxClient / 2 + 10, cyClient / 2 - 145);
	SelectObject(hdc, hOldBrush);

	//����
	hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	hOldBrush = SelectObject(hdc, hRedBrush);
	Ellipse(hdc, cxClient / 2 - 10, cyClient / 2 - 135, cxClient / 2 + 10, cyClient / 2 - 115);
	SelectObject(hdc, hOldBrush);

	MoveToEx(hdc, cxClient / 2, cyClient / 2 - 115, NULL);
	LineTo(hdc, cxClient / 2, cyClient / 2 - 30);

	//���
	Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 120, cxClient / 2 + 70, cyClient / 2 - 30,
		cxClient / 2 - 60, cyClient / 2 - 50, cxClient / 2 + 60, cyClient / 2 - 50);

	//����  ������
	MoveToEx(hdc, cxClient / 2 + 20, cyClient / 2 - 85, NULL);
	LineTo(hdc, cxClient / 2 + 75, cyClient / 2 - 85);
	MoveToEx(hdc, cxClient / 2 - 20, cyClient / 2 - 85, NULL);
	LineTo(hdc, cxClient / 2 - 75, cyClient / 2 - 85);

	MoveToEx(hdc, cxClient / 2 + 20, cyClient / 2 - 95, NULL);
	LineTo(hdc, cxClient / 2 + 70, cyClient / 2 - 105);
	MoveToEx(hdc, cxClient / 2 - 20, cyClient / 2 - 95, NULL);
	LineTo(hdc, cxClient / 2 - 70, cyClient / 2 - 105);

	MoveToEx(hdc, cxClient / 2 + 20, cyClient / 2 - 75, NULL);
	LineTo(hdc, cxClient / 2 + 70, cyClient / 2 - 65);
	MoveToEx(hdc, cxClient / 2 - 20, cyClient / 2 - 75, NULL);
	LineTo(hdc, cxClient / 2 - 70, cyClient / 2 - 65);

	//����
	hOldBrush = SelectObject(hdc, hBlueBrush);
	Rectangle(hdc, cxClient / 2 - 100, cyClient / 2 - 10, cxClient / 2 + 100, cyClient / 2 + 150);
	SelectObject(hdc, hOldBrush);

	//��Ƥ
	Ellipse(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120);//Բ
	hPen = CreatePen(PS_DOT, 1, RGB(255, 255, 255));//������Ƥ������������Բ��
	hOldPen = SelectObject(hdc, hPen);
	Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120,
		cxClient / 2 + 60, cyClient / 2 - 10, cxClient / 2 - 60, cyClient / 2 - 10);
	SelectObject(hdc, hOldPen);

	//Χ��
	hOldBrush = SelectObject(hdc, hRedBrush);
	RoundRect(hdc, cxClient / 2 - 102, cyClient / 2 - 12, cxClient / 2 + 102, cyClient / 2 + 5, 20, 20);
	SelectObject(hdc, hOldBrush);

	//����
	hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	hOldBrush = SelectObject(hdc, hYellowBrush);
	Ellipse(hdc, cxClient / 2 - 12, cyClient / 2 - 4, cxClient / 2 + 12, cyClient / 2 + 20);
	RoundRect(hdc, cxClient / 2 - 12, cyClient / 2 + 3, cxClient / 2 + 12, cyClient / 2 + 6, 20, 20);
	SelectObject(hdc, hRedBrush);
	Ellipse(hdc, cxClient / 2 - 5, cyClient / 2 + 8, cxClient / 2 + 5, cyClient / 2 + 18);
	SelectObject(hdc, hOldBrush);

	//����
	Ellipse(hdc, cxClient / 2 - 20, cyClient / 2 + 130, cxClient / 2 + 20, cyClient / 2 + 170);//��Բ
	hPen = CreatePen(PS_DOT, 1, RGB(255, 255, 255));	//������Ƥ������������Բ��
	hOldPen = SelectObject(hdc, hPen);
	Arc(hdc, cxClient / 2 - 20, cyClient / 2 + 130, cxClient / 2 + 20, cyClient / 2 + 170,
		cxClient / 2 - 20, cyClient / 2 + 150, cxClient / 2 + 20, cyClient / 2 + 150);
	SelectObject(hdc, hOldPen);

	//�ڴ�
	Pie(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100,
		cxClient / 2 - 50, cyClient / 2 + 50, cxClient / 2 + 50, cyClient / 2 + 50);
	/*Pie(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100,
		cxClient / 2 - 50, cyClient / 2 + 50, cxClient / 2 + 50, cyClient / 2 + 50);
		������ʱ����ʱ���*/

		//����
		/*Ellipse(hdc, cxClient / 2 - 100, cyClient / 2 + 130, cxClient / 2 - 20, cyClient / 2 + 170);
		Ellipse(hdc, cxClient / 2 + 20, cyClient / 2 + 130, cxClient / 2 + 100, cyClient / 2 + 170);*/
	Ellipse(hdc, cxClient / 2 - 110, cyClient / 2 + 135, cxClient / 2 - 10, cyClient / 2 + 165);
	Ellipse(hdc, cxClient / 2 + 10, cyClient / 2 + 135, cxClient / 2 + 110, cyClient / 2 + 165);

	//�첲
	hOldBrush = SelectObject(hdc, hBlueBrush);
	apt[0].x = cxClient / 2 - 100;
	apt[0].y = cyClient / 2;
	apt[1].x = cxClient / 2 - 150;
	apt[1].y = cyClient / 2 + 60;
	apt[2].x = cxClient / 2 - 140;
	apt[2].y = cyClient / 2 + 80;
	apt[3].x = cxClient / 2 - 100;
	apt[3].y = cyClient / 2 + 60;
	//���ǰ�˳�����ӵģ������Ǵ�������
	/*apt[0].x = cxClient / 2 - 100;
	apt[0].y = cyClient / 2;
	apt[1].x = cxClient / 2 - 150;
	apt[1].y = cyClient / 2 + 60;
	apt[3].x = cxClient / 2 - 140;
	apt[3].y = cyClient / 2 + 80;
	apt[2].x = cxClient / 2 - 100;
	apt[2].y = cyClient / 2 + 60;*/
	Polygon(hdc, apt, 4);
	SelectObject(hdc, hOldBrush);
	Ellipse(hdc, cxClient / 2 - 168, cyClient / 2 + 60, cxClient / 2 - 138, cyClient / 2 + 90);	//������

	hOldBrush = SelectObject(hdc, hBlueBrush);
	apt[0].x = cxClient / 2 + 100;
	apt[0].y = cyClient / 2;
	apt[1].x = cxClient / 2 + 150;
	apt[1].y = cyClient / 2 + 60;
	apt[2].x = cxClient / 2 + 140;
	apt[2].y = cyClient / 2 + 80;
	apt[3].x = cxClient / 2 + 100;
	apt[3].y = cyClient / 2 + 60;
	Polygon(hdc, apt, 4);
	SelectObject(hdc, hOldBrush);
	Ellipse(hdc, cxClient / 2 + 168, cyClient / 2 + 60, cxClient / 2 + 138, cyClient / 2 + 90);	//������

	//ȥ�����ߣ���ǿ�����
	hPen = CreatePen(PS_SOLID, 2, RGB(0, 159, 232));
	hOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, cxClient / 2 - 100, cyClient / 2, NULL);;
	LineTo(hdc, cxClient / 2 - 100, cyClient / 2 + 50);;

	MoveToEx(hdc, cxClient / 2 + 100, cyClient / 2, NULL);;
	LineTo(hdc, cxClient / 2 + 100, cyClient / 2 + 50);
	SelectObject(hdc, hOldPen);
}