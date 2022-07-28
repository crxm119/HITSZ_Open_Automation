#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include<graphics.h>
#include "function.h"
#define SIZE 34
#define W 20
#define H 20
#define WIDTH 700
#define HIGH 800

int x0 = 10;
int y0 = HIGH-H*SIZE-10;
int map[H][W] = { 0 };
int box_kind;
int movekind, moveresult;
int tempposition[2][4] = { -2 };//��¼��ǰλ��
int temp[2][4] = { -2 };//��¼��ʱλ��
int score = 0;
int kind=1;
void startup()
{
	int i, j;
	initgraph(WIDTH, HIGH);
	BeginBatchDraw();
	boxstartup();
}
void Show()
{
	IMAGE img_bk, img_box1, img_box2;
	loadimage(&img_bk, "����˹�����ز�\\bk1.jpg");
	loadimage(&img_box1, "����˹�����ز�\\box_1.jpg", 6 * SIZE, SIZE);
	putimage(0, 0, &img_bk);
	int i, j, k;
	char str[10];
	_itoa_s(score, str, 10);
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("��Բ"));
	outtextxy(40, 40, "����:");
	outtextxy(100, 40, str);
	//���Ʋο���
	setcolor(RED);
	for (i = 0; i <= H; i++)
	{
		line(x0, y0 + i * SIZE, x0 + W * SIZE, y0 + i * SIZE);
	}
	for (i = 0; i <= W; i++)
	{
		line(x0 + i * SIZE, y0, x0 + i * SIZE, y0 + H * SIZE);
	}
	//����map��ͼ��
	for (i = 0; i <= H - 1; i++)
	{
		for (j = 0; j <= W - 1; j++)
		{
			if (map[i][j] > 0)
			{
				putimage(x0 + j * SIZE, y0 + i * SIZE, SIZE, SIZE, &img_box1, (map[i][j] - 1) * SIZE, 0);
			}
		}
	}
	//��������ͼ��tempposition
	for (i = 0; i < 4; i++)
	{
		if (tempposition[0][i] != -1 && tempposition[1][i] >= 0)
			putimage(x0 + tempposition[0][i] * SIZE, y0 + tempposition[1][i] * SIZE, SIZE, SIZE, &img_box1, (box_kind - 1) * SIZE, 0);
	}
	if (score < 10*W)
	{
		Sleep(250);
	}
	else
	{
		Sleep(150);
	}
	FlushBatchDraw();
}
void Updatewithoutinput()
{
	int i, j, k;
	int success;//success���ÿ���Ƿ�ɹ�
	moveresult = Move(1);
	if (moveresult == 0)
	{
		for (i = 0; i<4 && tempposition[0][i] > -1; i++)
		{
			if (tempposition[1][i] > -1)
				map[tempposition[1][i]][tempposition[0][i]] = box_kind;
			if (tempposition[1][i] < 0)
			{
				setfillcolor(BLACK);
				fillrectangle(0, 0, WIDTH, HIGH);
				settextstyle(40, 0, _T("��Բ"));
				outtextxy(WIDTH / 2 - 280, HIGH / 2 - 40, "��Ϸ����:��Ctrl+W�˳�...");
				char str[10];
				_itoa_s(score, str, 10);
				outtextxy(WIDTH / 2 - 120, HIGH / 2 + 10, "������");
				outtextxy(WIDTH / 2, HIGH / 2 + 10, str);
				FlushBatchDraw();
				while (1)
				{
					if ((GetAsyncKeyState(VK_CONTROL) & 0x8000))
					{
						if ((GetAsyncKeyState(0x57) & 0x8000))
						{
							EndBatchDraw();
							closegraph();
							exit(0);
						}
					}
				}
			}
		}
		boxstartup();
	}
	for (i = H-1; i >=0; i--)
	{
		success = 1;
		for (j = 0; j < W; j++)
		{
			if (!map[i][j])
				success = 0;
		}
		if (success == 1)
		{
			for (k = i; k >= 0; k--)
			{
				if (k > 0)
				{
					for (j = 0; j < W; j++)
					{
						map[k][j] = map[k - 1][j];
					}
				}
				else
				{
					for (j = 0; j < W; j++)
					{
						map[0][j] = 0;
					}
				}
			}
			score += W;
		}
	}
}
void Updatewithinput()
{
	int i, j;
	if (_kbhit())
	{
		if (((GetAsyncKeyState(83) || GetAsyncKeyState(VK_DOWN)) && 0x8000))//����
		{
			Move(1);
		}
		if (((GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) && 0x8000))//����
		{
			Move(2);
		}
		if (((GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)) && 0x8000))//����
		{
			Move(3);
		}
		if ((GetAsyncKeyState(VK_SPACE) && 0x8000))//��ʱ����ת
		{
			Move(4);
		}
	}
}
void boxstartup()//���ڴ���������״�������Ϣ�����ʼ��
{
	int i;
	//box_kind��ʼ��
	srand(time(NULL));
	box_kind = rand() % 6 + 1;
	int kind = rand() % 4 + 1;
	//tempposition��ʼ��
	for (i = 0; i < 4; i++)
	{
		tempposition[0][i] = -2;
		tempposition[1][i] = -2;
	}
	if (box_kind == 1)
	{
		if (kind == 1 || kind == 3)
		{
			for (i = 0; i < 4; i++)
			{
				tempposition[0][i] = 7;
				tempposition[1][i] = i - 4;
			}
		}
		if (kind == 2 || kind == 4)
		{
			for (i = 0; i < 4; i++)
			{
				tempposition[0][i] = i+6;
				tempposition[1][i] = -1;
			}
		}
	}
	if (box_kind == 2)
	{
		if (kind == 1) 
		{
			for (i = 0; i < 3; i++)
			{
				tempposition[0][i] = 7;
				tempposition[1][i] = i - 3;
			}
			tempposition[0][3] = 8;
			tempposition[1][3] = -1;
		}
		if (kind == 2)
		{
			for (i = 0; i < 3; i++)
			{
				tempposition[0][i] = 7;
				tempposition[1][i] = i - 3;
			}
			tempposition[0][3] = 8;
			tempposition[1][3] = -1;

			tempposition[0][1] = 8;
			tempposition[0][0] = 6;
			tempposition[1][0] = -1;
		}
		if (kind == 3)
		{
			for (i = 0; i < 3; i++)
			{
				tempposition[0][i] = 7;
				tempposition[1][i] = i - 3;
			}
			tempposition[0][3] = 8;
			tempposition[1][3] = -1;

			tempposition[0][2] = 8;
			tempposition[1][2] = -3;
			tempposition[0][1] = 8;
		}
		if (kind == 4)
		{
			for (i = 0; i < 3; i++)
			{
				tempposition[0][i] = i + 6;
				tempposition[1][i] =-2;
			}
			tempposition[0][3] = 6;
			tempposition[1][3] = -1;


		}
	}
	if (box_kind == 3)
	{
		if (kind == 1 || kind == 3)
		{
			for (i = 0; i < 3; i++)
			{
				tempposition[0][i] = 7;
				tempposition[1][i] = i - 3;
			}
		}
		if (kind == 2 || kind == 4)
		{
			for (i = 0; i < 3; i++)
			{
				tempposition[0][i] = i+6;
				tempposition[1][i] = -1;
			}
		}
	}
	if (box_kind == 4)
	{
		if (kind == 1)
		{
			tempposition[0][0] = 7;
			tempposition[1][0] = tempposition[1][1] = -2;
			tempposition[0][1] = 8;
			tempposition[0][2] = 7;
			tempposition[1][2] = -1;
		}
		if (kind == 2)
		{
			tempposition[0][0] = 7;
			tempposition[1][0] = -2;
			tempposition[0][1] = 8;
			tempposition[0][2] = 7;
			tempposition[1][2] = tempposition[1][1]= -1;
		}
		if (kind == 3)
		{
			tempposition[0][0] = 8;
			tempposition[1][1] = -2;
			tempposition[0][1] = 8;
			tempposition[0][2] = 7;
			tempposition[1][0] = tempposition[1][2] = -1;
		}
		if (kind == 4)
		{
			tempposition[0][0] = 7;
			tempposition[1][0] = tempposition[1][1] = -2;
			tempposition[0][1] = 8;
			tempposition[0][2] = 8;
			tempposition[1][2] = -1;
		}
	}
	if (box_kind == 5)
	{
		tempposition[0][0] = 7; tempposition[1][0] = -1;
	}
	if (box_kind == 6)
	{
		tempposition[0][0] = tempposition[0][2] = 7;
		tempposition[0][1] = tempposition[0][3] = 8;
		tempposition[1][0] = tempposition[1][1] = -2;
		tempposition[1][2] = tempposition[1][3] = -1;
	}
}
int Move(int movekind)//kind:Ϊ1���£�Ϊ2����Ϊ3���ң�Ϊ4��ת; ����0��ʾ�ƶ�ʧ��
{
	int i, result = 0;
	//tempposition��ֵ��temp
	for (i = 0; i < 4; i++)
	{
		temp[0][i] = tempposition[0][i];
		temp[1][i] = tempposition[1][i];
	}
	if (movekind == 1)//����
	{
		result = 1;
		for (i = 0; i < 4 && temp[0][i] > -1; i++)
			temp[1][i]++;
		for (i = 0; i < 4; i++)
		{
			if (temp[1][i] > H - 1)
				return 0;//����߽�
		}
		for (i = 0; i < 4; i++)
		{
			if (-1 < temp[0][i] && temp[0][i] < W && -1 < temp[1][i] && temp[1][i] < H)
			{
				if (map[temp[1][i]][temp[0][i]] > 0)
					return 0;//�ص�
			}
		}
	}
	if (movekind == 2)//����
	{
		result = 1;
		for (i = 0; i < 4 && temp[0][i] > -1; i++)
		{
			temp[0][i]--;
		}
		for (i = 0; i < 4; i++)
		{
			if (temp[0][i] > -2)
			{
				if (temp[0][i] < 0)
					return 0;//������߽�
			}

		}
		for (i = 0; i < 4; i++)
		{
			if (-1 < temp[0][i] && temp[0][i] < W && -1 < temp[1][i] && temp[1][i] < H)
			{
				if (map[temp[1][i]][temp[0][i]] > 0)
					return 0;//�ص�
			}
		}
	}
	if (movekind == 3)//����
	{
		result = 1;
		for (i = 0; i < 4 && temp[0][i] > -1; i++)
		{
			temp[0][i]++;
		}
		for (i = 0; i < 4; i++)
		{
			if (temp[0][i] > -2)
			{
				if (temp[0][i] >= W)
					return 0;//�����ұ߽�
			}
		}
		for (i = 0; i < 4; i++)
		{
			if (-1 < temp[0][i] && temp[0][i] < W && -1 < temp[1][i] && temp[1][i] < H)
			{
				if (map[temp[1][i]][temp[0][i]] > 0)
					return 0;//�ص�
			}
		}
	}

	if (result == 1)
	{
		for (i = 0; i < 4; i++)
		{
			tempposition[0][i] = temp[0][i];
			tempposition[1][i] = temp[1][i];
		}
	}
	return result;
}