#include<time.h>
#include<Windows.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include"function.h"

#define HIGH 864
#define WIDTH 1536
#define SIZE 50
#define BRICKMAX 80
#define BOXMAX 10

int viewchoice = 1;//1�����ʼ���棬2����ؿ�ѡ����棬3������Ϸ����
int gamechoice;//��¼�ؿ�ֵ
int high;//ÿ��y��������ж��ٿ�ש
int width;//ÿ��x��������ж��ٿ�ש
int size;//���ڼ�¼ÿ�صĳߴ�
int brickposition[2][BRICKMAX] = { 0 };//��¼ש��λ��
int boxposition[2][BOXMAX] = { 0 };//��¼����λ��
int aimposition[2][BOXMAX] = { 0 };//��¼���ӵ�Ŀ��λ��
int position_x, position_y;//��¼������λ��
int distance = 0;
int movetype = { 0 }, movechoice = 0;
int redotimes = 5;
int levelsteps[2][10] = { 0 };//��¼ÿ���Ƿ�ͨ���Ͳ���
SYSTEMTIME time1;

void Startup()
{
	GetLocalTime(&time1);
	initgraph(WIDTH, HIGH);
	BeginBatchDraw();
	Welcome();
}
void Welcome()
{
	//������Ļ��СΪWIDTH*1280��Ϊ16��9�ĳ����
	setbkcolor(BLACK);								//���ñ�����ɫΪ��ɫ
	cleardevice();									//����

	Printtext1();									//�����Ϣ��ͣ��1��
	Sleep(2000);

	for (int colorchange = 255; colorchange >= 0; colorchange--)
	{
		settextcolor(RGB(colorchange, colorchange, colorchange));
		Printtext1();								//������ɫ����
		Sleep(10);
	}

	cleardevice();									//����

	Printtext2();
	Sleep(2000);

	for (int colorchange = 0; colorchange <= 255; colorchange++)
	{
		setbkcolor(RGB(colorchange, colorchange, colorchange));
		cleardevice();
		Printtext2();								//������ɫ����
		Sleep(12);
	}
}
void Printtext1()
{
	LOGFONT f;									// �ýṹ������������ԡ������г��������õõ������ԣ�ƽ���޸�ʱֻ�޸ı仯��
	gettextstyle(&f);							// ��ȡ��ǰ��������
	f.lfEscapement = 0;							// �����ַ���������̧�Ƕ�Ϊ0
	f.lfOrientation = 0;						// ����ÿ���ַ���ʱ����ת�Ƕ�Ϊ0
	f.lfWeight = 300;							// ���ñʻ���ϸΪLIGHT
	f.lfItalic = 0;								// ����Ϊ��б��
	f.lfUnderline = 1;							// ����Ϊ���»���
	f.lfStrikeOut = 0;							// ����Ϊ����ɾ����
	f.lfQuality = PROOF_QUALITY;				// �������ֵ��������Ϊ��������
	settextstyle(&f);							// ������������
	settextstyle(72, 0, _T("�����ֺ��μ���"));	// ��������߶�Ϊ 42������ƽ�����Ϊ����Ӧ������Ϊ�����ֺ��μ���

	RECT r = { 0, 50, WIDTH, HIGH };
	drawtext(_T("������Ա"), &r, DT_CENTER);		//������ʾ
	r = { 0, 310, WIDTH, HIGH };
	drawtext(_T("ѧ       ��"), &r, DT_CENTER);
	r = { 0, 570, WIDTH, HIGH };
	drawtext(_T("ָ����ʦ"), &r, DT_CENTER);

	f.lfUnderline = 0;							// ����Ϊ�����»���
	settextstyle(&f);							// ������������
	settextstyle(72, 0, _T("�����ֺ��μ���"));

	r = { 0, 170, WIDTH, HIGH };
	drawtext(_T("���Զ       ��Ң    "), &r, DT_CENTER);
	r = { 0, 430, WIDTH, HIGH };
	drawtext(_T("180610112    190410102"), &r, DT_CENTER);
	r = { 0, 690, WIDTH, HIGH };
	drawtext(_T("������    �ǳ���"), &r, DT_CENTER);

	FlushBatchDraw();
}
void Printtext2()
{
	settextcolor(WHITE);

	LOGFONT f;									// �ýṹ������������ԡ������г��������õõ������ԣ�ƽ���޸�ʱֻ�޸ı仯��
	gettextstyle(&f);							// ��ȡ��ǰ��������
	f.lfEscapement = 0;							// �����ַ���������̧�Ƕ�Ϊ0
	f.lfOrientation = 0;						// ����ÿ���ַ���ʱ����ת�Ƕ�Ϊ0
	f.lfWeight = 300;							// ���ñʻ���ϸΪLIGHT
	f.lfItalic = 0;								// ����Ϊ��б��
	f.lfUnderline = 0;							// ����Ϊ�����»���
	f.lfStrikeOut = 0;							// ����Ϊ����ɾ����
	f.lfQuality = PROOF_QUALITY;				// �������ֵ��������Ϊ��������
	settextstyle(&f);							// ������������
	settextstyle(120, 0, _T("�����ֺ��μ���"));	// ��������߶�Ϊ 120������ƽ�����Ϊ����Ӧ������Ϊ�����ֺ��μ���

	RECT r = { 0, 120, WIDTH, HIGH };
	drawtext(_T("�߼����Գ������"), &r, DT_CENTER);		//������ʾ
	r = { 0, 300, WIDTH, HIGH };
	drawtext(_T("�γ����"), &r, DT_CENTER);

	f.lfUnderline = 1;							// ����Ϊ���»���
	settextstyle(&f);							// ������������
	settextstyle(108, 0, _T("�����ֺ��μ���"));

	r = { 0, 570, WIDTH, HIGH };
	drawtext(_T("������"), &r, DT_CENTER);

	f.lfUnderline = 0;							// ����Ϊ�����»���
	settextstyle(&f);							// ������������

	FlushBatchDraw();
}
void Show()
{
	if (viewchoice == 1)
	{
		View1();
	}
	if (viewchoice == 2)
	{
		View2();
	}
	if (viewchoice == 3)
	{
		View3();
	}
}
void View1()
{
	int i, j;
	IMAGE img_backgroundbrick, img_box;
	loadimage(&img_backgroundbrick, "C:\\�������ز�\\backgroundbrick.jpg");
	loadimage(&img_box, "C:\\�������ز�\\box.jpg", 2.5 * SIZE, 2.5 * SIZE);

	//�̵ذ屳��ͼ 
	for (i = 1; i <= WIDTH / SIZE + 1; i++)
	{
		for (j = 1; j <= HIGH / 2 / SIZE + 1; j++)
		{
			putimage((i - 1) * SIZE, (j - 1) * 2 * SIZE, &img_backgroundbrick);
		}
	}

	//�����Ϸ��������ӡ����·�����ʼ��
	setbkmode(TRANSPARENT);
	settextstyle(150, 0, _T("�����ֺ��μ���"));
	RECT r = { 0, 100, WIDTH, HIGH };
	drawtext(_T("������"), &r, DT_CENTER);
	r = { 0, 500, WIDTH, HIGH };
	drawtext(_T("��ʼ"), &r, DT_CENTER);
	//rectangle(WIDTH / 2 - 140, 520, WIDTH / 2 + 120, 620);

	//������������ͼ��
	putimage(WIDTH / 2 - 2.5 * SIZE / 2, 300, &img_box);
	FlushBatchDraw();
}
void View2()
{
	int i, j, k;
	IMAGE  img_esc1, img_esc2, img_guanqia1, img_guanqia2, img_backgroundbrick;
	loadimage(&img_backgroundbrick, "C:\\�������ز�\\backgroundbrick.jpg");
	loadimage(&img_esc1, "C:\\�������ز�\\esc_1.jpg");
	loadimage(&img_esc2, "C:\\�������ز�\\esc_2.jpg");
	loadimage(&img_guanqia1, "C:\\�������ز�\\guanqia_1.jpg");
	loadimage(&img_guanqia2, "C:\\�������ز�\\guanqia_2.jpg");
	//�̵ذ屳��ͼ 
	for (i = 1; i <= WIDTH / SIZE + 1; i++)
	{
		for (j = 1; j <= HIGH / 2 / SIZE + 1; j++)
		{
			putimage((i - 1) * SIZE, (j - 1) * 2 * SIZE, &img_backgroundbrick);
		}
	}

	//���ƹؿ�ͼ��
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 3; j++)
		{
			putimage(i / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia2, NOTSRCERASE);
			putimage(i / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia1, SRCINVERT);
		}
	}
	putimage(1 / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia2, NOTSRCERASE);
	putimage(1 / 4.0 * WIDTH - SIZE, 200 + (j - 1) * 140, &img_guanqia1, SRCINVERT);

	//���Ʒ���ͼ��
	putimage(110, 40, &img_esc2, NOTSRCERASE);
	putimage(110, 40, &img_esc1, SRCINVERT);
	//rectangle(10, 20, 10 + 88, 20 + 88 + 30);

	//���ƹؿ�����
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, _T("�����ֺ��μ���"));
	char str[10];
	k = 1;
	for (j = 1; j <= 3; j++)
	{
		for (i = 1; i <= 3; i++)
		{
			_itoa_s(k, str, 10);
			outtextxy(i / 4.0 * WIDTH - SIZE + 20, 200 + (j - 1) * 140, str);
			k++;
		}
	}
	_itoa_s(k, str, 10);
	outtextxy(1 / 4.0 * WIDTH - SIZE + 10, 210 + 3 * 140, str);

	//�������Ϸ����ؿ�ѡ�񡱱���
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(100, 0, _T("�����ֺ��μ���"));
	RECT r = { 0, 50, WIDTH, HIGH };
	drawtext(_T("�ؿ�ѡ��"), &r, DT_CENTER);
	//outtextxy(180, 30, "�ؿ�ѡ��");

	//�������Ϸ������ء�
	settextstyle(60, 0, _T("�����ֺ��μ���"));
	outtextxy(100, 100, "����");
	FlushBatchDraw();
}
void View3()
{
	int i, j;
	IMAGE img_backgroundbrick, img_brick, img_box, img_man1, img_man2, img_successbox, img_aim1, img_aim2, img_up, img_down, img_left, img_right, img_menu1, img_menu2;
	loadimage(&img_backgroundbrick, "C:\\�������ز�\\backgroundbrick.jpg", size / 2, size);
	loadimage(&img_man1, "C:\\�������ز�\\man_1.jpg", size, size);
	loadimage(&img_man2, "C:\\�������ز�\\man_2.jpg", size, size);
	loadimage(&img_menu1, "C:\\�������ز�\\menu_1.jpg", 3 * SIZE, 3 * SIZE * 128 / 268);
	loadimage(&img_menu2, "C:\\�������ز�\\menu_2.jpg", 3 * SIZE, 3 * SIZE * 128 / 268);
	loadimage(&img_brick, "C:\\�������ز�\\brick.jpg", size, size);
	loadimage(&img_aim1, "C:\\�������ز�\\aim_1.jpg", size, size);
	loadimage(&img_aim2, "C:\\�������ز�\\aim_2.jpg", size, size);
	loadimage(&img_box, "C:\\�������ز�\\box.jpg", size, size);
	loadimage(&img_successbox, "C:\\�������ز�\\successbox.jpg", size, size);
	loadimage(&img_up, "C:\\�������ز�\\up.jpg", size, size);
	loadimage(&img_down, "C:\\�������ز�\\down.jpg", size, size);
	loadimage(&img_left, "C:\\�������ز�\\left.jpg", size, size);
	loadimage(&img_right, "C:\\�������ز�\\right.jpg", size, size);
	//���Ƶذ屳��ͼ
	cleardevice();
	for (i = 1; i <= WIDTH / (size / 2) + 1; i++)
	{
		for (j = 1; j <= HIGH / size + 1; j++)
		{
			putimage((i - 1) * size / 2, (j - 1) * size, &img_backgroundbrick);
		}
	}
	//���Ʋ˵���ʾ��ʶ
	putimage(850, 50, &img_menu2, NOTSRCERASE);
	putimage(850, 50, &img_menu1, SRCINVERT);
	putimage(850, 150, &img_menu2, NOTSRCERASE);
	putimage(850, 150, &img_menu1, SRCINVERT);
	putimage(850, 250, &img_menu2, NOTSRCERASE);
	putimage(850, 250, &img_menu1, SRCINVERT);
	putimage(850, 350, &img_menu2, NOTSRCERASE);
	putimage(850, 350, &img_menu1, SRCINVERT);
	putimage(850, 450, &img_menu2, NOTSRCERASE);
	putimage(850, 450, &img_menu1, SRCINVERT);
	putimage(850, 550, &img_menu2, NOTSRCERASE);
	putimage(850, 550, &img_menu1, SRCINVERT);

	char str[10];
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("�����ֺ��μ���"));
	_itoa_s(gamechoice, str, 10);
	outtextxy(890, 50, "�ؿ�");
	outtextxy(905, 85, str);
	_itoa_s(distance, str, 10);
	outtextxy(890, 150, "����");
	outtextxy(905, 185, str);
	outtextxy(860, 250, "��������");
	_itoa_s(redotimes, str, 10);
	outtextxy(910, 285, str);
	settextstyle(60, 0, _T("�����ֺ��μ���"));
	outtextxy(850, 355, "������");
	outtextxy(870, 450, "����");
	outtextxy(870, 550, "����");
	setcolor(YELLOW);
	settextstyle(40, 0, _T("�����ֺ��μ���"));
	outtextxy(1050, 50, "����˵����");
	outtextxy(1050, 110, "��:����W/w/�� ������ϱ�");
	outtextxy(1050, 170, "��:����S/s/�� ������±�");
	outtextxy(1050, 230, "��:����A/a/�� ��������");
	outtextxy(1050, 290, "��:����D/d/�� ������ұ�");
	outtextxy(1050, 350, "ÿ�ֿɳ�������Ϊ5");
	outtextxy(1050, 410, "�˳���Ϸ��Ctrl+w");

	//����box
	for (i = 0; boxposition[0][i] > 0; i++)
	{
		putimage((boxposition[0][i]) * size, (boxposition[1][i]) * size, &img_box);
	}
	//����ש��
	for (i = 0; brickposition[0][i] > 0; i++)
	{
		putimage((brickposition[0][i]) * size, (brickposition[1][i]) * size, &img_brick);
	}
	//����aim��
	for (i = 0; aimposition[0][i] > 0; i++)
	{
		putimage((aimposition[0][i]) * size, (aimposition[1][i]) * size, &img_aim2, NOTSRCERASE);
		putimage((aimposition[0][i]) * size, (aimposition[1][i]) * size, &img_aim1, SRCINVERT);
	}
	//���Ƴɹ��Ŀ�
	for (i = 0; aimposition[0][i] > 0; i++)
	{
		for (j = 0; boxposition[0][j] > 0; j++)
		{
			if (aimposition[0][i] == boxposition[0][j] && aimposition[1][i] == boxposition[1][j])
			{
				putimage((aimposition[0][i]) * size, (aimposition[1][i]) * size, &img_successbox);
			}
		}
	}
	//������
	putimage((position_x) * size, (position_y) * size, &img_man2, NOTSRCERASE);
	putimage((position_x) * size, (position_y) * size, &img_man1, SRCINVERT);
	//�����������ұ�ʶ
	putimage((WIDTH / size - 3) * size, (HIGH / size - 3.5) * size, &img_up);
	putimage((WIDTH / size - 3) * size, (HIGH / size - 2) * size, &img_down);
	putimage((WIDTH / size - 4.5) * size, (HIGH / size - 2) * size, &img_left);
	putimage((WIDTH / size - 1.5) * size, (HIGH / size - 2) * size, &img_right);
	FlushBatchDraw();
}
void Mapreset()//��ʼ��ש�飬���ӣ��ˣ�����Ŀ��λ��
{
	int i, j;

	//����brickposition
	for (i = 0; i < BRICKMAX; i++)
	{
		brickposition[0][i] = 0;
		brickposition[1][i] = 0;
	}
	//����boxposition,aimposition
	for (i = 0; i < BOXMAX; i++)
	{
		boxposition[0][i] = 0;
		boxposition[1][i] = 0;
		aimposition[0][i] = 0;
		aimposition[1][i] = 0;
	}
	distance = 0;
	movechoice = 0;
	movetype = 0;
	redotimes = 5;
	//����brickposition��boxposition��aimposition,position_x,position_y��size
	//��һ��
	if (gamechoice == 1)
	{
		int brickposition1[2][28] = { {3,4,5,5,5,6,7,8,8,8,7,6,6,6,6,5,4,4,4,3,2,1,1,1,2,3,3,3}, {1,1,1,2,3,3,3,3,4,5,5,5,6,7,8,8,8,7,6,6,6,6,5,4,4,4,3,2} };
		for (i = 0; i < 28; i++)
		{
			brickposition[0][i] = brickposition1[0][i];
			brickposition[1][i] = brickposition1[1][i];
		}
		int boxposition1[2][4] = { { 4,6,4,5 }, { 4,4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				boxposition[i][j] = boxposition1[i][j];			//�����һ�����ӳ�ʼλ��
			}
		}

		int aimposition1[2][4] = { { 4,7,2,5 }, { 2,4,5,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				aimposition[i][j] = aimposition1[i][j];			//�����һ������Ŀ��λ��
			}
		}
		position_x = 5; position_y = 5;

		width = 8; 
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 2)	//�ڶ���
	{
		int brickposition2[2][39] = { { 1,2,3,4,5,5,5,5,5,6,7,7,7,8,9,9,9,9,9,9,8,7,6,6,6,5,4,3,2,2,2,2,3,3,2,1,1,1,1 }, { 1,1,1,1,1,2,3,4,5,5,5,4,3,3,3,4,5,6,7,8,8,8,8,7,9,9,9,9,9,8,7,6,6,5,5,5,4,3,2 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 38; j++)
			{
				brickposition[i][j] = brickposition2[i][j];
			}
		}

		int boxposition2[2][3] = { { 3,4,3 }, { 3,3,4 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				boxposition[i][j] = boxposition2[i][j];			//����ڶ������ӳ�ʼλ��
			}
		}

		int aimposition2[2][3] = { { 8,8,8 }, { 4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				aimposition[i][j] = aimposition2[i][j];			//����ڶ�������Ŀ��λ��
			}
		}
		position_x = 2; position_y = 2;

		width = 9; 
		high = 9;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 3)	//������
	{
		int brickposition3[2][35] = { { 2,3,4,5,6,7,8,8,9,10,10,10,10,9,9,9,8,7,6,5,5,5,4,3,2,2,1,1,1,1,2,2,4,5,6 }, { 1,1,1,1,1,1,1,2,2,2,3,4,5,5,6,7,7,7,7,7,6,5,7,7,7,6,6,5,4,3,3,2,3,3,3 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 34; j++)
			{
				brickposition[i][j] = brickposition3[i][j];
			}
		}

		int boxposition3[2][4] = { { 3,5,8,7 }, { 3,4,4,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				boxposition[i][j] = boxposition3[i][j];			//������������ӳ�ʼλ��
			}
		}

		int aimposition3[2][4] = { { 3,4,3,4 }, { 5,5,6,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 3; j++)
			{
				aimposition[i][j] = aimposition3[i][j];			//�������������Ŀ��λ��
			}
		}
		position_x = 3; position_y = 4;
		
		width = 10; 
		high = 7;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 4)	//���Ĺ�
	{
		int brickposition4[2][26] = { { 2,3,4,5,5,5,5,6,6,6,6,6,5,4,3,2,1,1,1,1,2,2,1,1,1,2 }, { 1,1,1,1,2,3,4,4,5,6,7,8,8,8,8,8,8,7,6,5,5,4,4,3,2,2 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 25; j++)
			{
				brickposition[i][j] = brickposition4[i][j];
			}
		}

		int boxposition4[2][5] = { { 3,3,4,3,4 }, { 3,4,5,6,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition4[i][j];			//������Ĺ����ӳ�ʼλ��
			}
		}

		int aimposition4[2][5] = { { 2,2,3,4,5 }, { 6,7,7,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition4[i][j];			//������Ĺ�����Ŀ��λ��
			}
		}
		position_x = 2; position_y = 3;

		width = 6;
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 5)	//����� �ӱ��ؿ�ʼ���к���
	{
		int brickposition5[2][34] = { { 2,3,4,5,6,5,6,7,7,7,8,8,8,8,8,7,6,5,4,3,2,1,1,1,1,1,2,2,2,3,3,5,5,6 }, { 1,1,1,1,1,2,2,2,3,4,4,5,6,7,8,8,8,8,8,8,8,8,7,6,5,4,4,3,2,4,5,4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 33; j++)
			{
				brickposition[i][j] = brickposition5[i][j];
			}
		}

		int boxposition5[2][3] = { { 4,3,6 }, { 3,6,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				boxposition[i][j] = boxposition5[i][j];			//�����������ӳ�ʼλ��
			}
		}

		int aimposition5[2][3] = { { 2,2,2 }, { 5,6,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 2; j++)
			{
				aimposition[i][j] = aimposition5[i][j];			//������������Ŀ��λ��
			}
		}
		position_x = 3; position_y = 2;

		width = 8;
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 6)	//������
	{
		int brickposition6[2][62] = { { 1,2,3,4,4,5,6,7,8,9,10,10,10,10,11,11,11,11,11,12,13,13,13,13,12,11,10,9,9,8,8,7,6,5,4,3,2,2,2,2,1,1,1,1,1,1,6,7,8,9,9,9,6,5,4,3,3,3,5,8,7,4 }, { 2,2,2,2,1,1,1,1,1,1,1,2,3,4,4,5,6,7,8,8,8,9,10,11,11,11,11,11,10,10,11,11,11,11,11,11,11,10,9,8,8,7,6,5,4,3,3,3,3,6,7,8,9,9,9,6,5,4,4,5,8,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 60; j++)
			{
				brickposition[i][j] = brickposition6[i][j];
			}
		}

		int boxposition6[2][5] = { { 5,7,6,5,7 }, { 5,5,6,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition6[i][j];			//������������ӳ�ʼλ��
			}
		}

		int aimposition6[2][5] = { { 5,9,6,3,7 }, { 3,5,6,7,9 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition6[i][j];			//�������������Ŀ��λ��
			}
		}
		position_x = 12; position_y = 9;

		width = 13;
		high = 11;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 7)	//���߹�
	{
		int brickposition7[2][37] = { { 4,5,6,7,8,9,10,10,10,10,10,10,9,9,9,8,7,6,5,4,3,2,1,1,1,2,3,3,3,3,3,4,7,7,7,7,6 }, { 1,1,1,1,1,1,1,2,3,4,5,6,6,7,8,8,8,8,8,8,8,8,8,7,6,6,6,5,4,3,2,2,2,3,5,6,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 36; j++)
			{
				brickposition[i][j] = brickposition7[i][j];
			}
		}

		int boxposition7[2][5] = { { 4,6,8,5,5 }, { 4,4,4,5,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition7[i][j];			//������߹����ӳ�ʼλ��
			}
		}

		int aimposition7[2][5] = { { 2,3,4,5,6 }, { 7,7,7,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition7[i][j];			//������߹�����Ŀ��λ��
			}
		}
		position_x = 9; position_y = 2;

		width = 10;
		high = 8;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 8)	//�ڰ˹�
	{
		int brickposition8[2][32] = { { 1,2,2,3,4,4,5,6,7,8,9,9,9,10,10,10,9,9,9,8,7,6,6,5,4,3,2,1,1,1,6,7 }, { 3,3,2,2,2,1,1,1,1,1,1,2,3,3,4,5,5,6,7,7,7,7,6,6,6,6,6,6,5,4,3,3 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 31; j++)
			{
				brickposition[i][j] = brickposition8[i][j];
			}
		}

		int boxposition8[2][5] = { { 5,4,6,5,7 }, { 3,4,4,5,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition8[i][j];			//����ڰ˹����ӳ�ʼλ��
			}
		}

		int aimposition8[2][5] = { { 3,2,3,2,3 }, { 3,4,4,5,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition8[i][j];			//����ڰ˹�����Ŀ��λ��
			}
		}
		position_x = 9; position_y = 4;

		width = 10;
		high = 7;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 9)	//�ھŹ�
	{
		int brickposition9[2][46] = { { 2,3,4,5,6,7,8,9,10,10,10,10,10,10,11,11,11,11,10,9,8,7,7,6,5,4,3,2,1,1,1,1,2,2,2,2,2,5,6,5,6,7,8,8,4,4 }, { 1,1,1,1,1,1,1,1,1,2,3,4,5,6,6,7,8,9,9,9,9,9,8,9,9,9,9,9,9,8,7,6,6,5,4,3,2,2,2,4,4,4,5,6,6,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 45; j++)
			{
				brickposition[i][j] = brickposition9[i][j];
			}
		}

		int boxposition9[2][6] = { { 6,3,9,3,6,9 }, { 3,4,4,7,7,7 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 5; j++)
			{
				boxposition[i][j] = boxposition9[i][j];			//����ھŹ����ӳ�ʼλ��
			}
		}

		int aimposition9[2][6] = { { 5,6,7,5,6,7 }, { 5,5,5,6,6,6 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 5; j++)
			{
				aimposition[i][j] = aimposition9[i][j];			//����ھŹ�����Ŀ��λ��
			}
		}
		position_x = 9; position_y = 8;

		width = 11;
		high = 9;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
	if (gamechoice == 10)	//��ʮ��
	{
		int brickposition10[2][26] = { { 3,4,5,6,7,8,8,8,8,8,7,7,7,6,5,4,4,3,2,1,1,1,1,2,3,3 }, { 1,1,1,1,1,1,2,3,4,5,5,6,7,7,7,7,6,6,6,6,5,4,3,3,3,2 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 25; j++)
			{
				brickposition[i][j] = brickposition10[i][j];
			}
		}

		int boxposition10[2][5] = { { 4,5,6,4,3 }, { 3,3,3,4,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				boxposition[i][j] = boxposition10[i][j];			//�����ʮ�����ӳ�ʼλ��
			}
		}

		int aimposition10[2][5] = { { 5,6,4,5,6 }, { 4,4,5,5,5 } };
		for (i = 0; i <= 1; i++)
		{
			for (j = 0; j <= 4; j++)
			{
				aimposition[i][j] = aimposition10[i][j];			//�����ʮ������Ŀ��λ��
			}
		}
		position_x = 2; position_y = 4;

		width = 8;
		high = 7;
		size = min(HIGH / (high + 2), HIGH / (width + 2));
		if (size % 2 == 0)
		{
			size = size;
		}
		else
		{
			size = size - 1;
		}
	}
}
void Updatewithoutinput()
{
	int i, j, success = 0;
	for (i = 0; aimposition[0][i] > 0; i++)
	{
		for (j = 0; boxposition[0][j] > 0; j++)
		{
			if (aimposition[0][i] == boxposition[0][j] && aimposition[1][i] == boxposition[1][j])
				success++;
		}
	}

	if (viewchoice == 3 && success == i)
	{
		if (levelsteps[0][gamechoice - 1] == 0)
		{
			levelsteps[0][gamechoice - 1] = 1;
			levelsteps[1][gamechoice - 1] = distance;
		}
		else if (levelsteps[0][gamechoice - 1] == 1)
		{
			levelsteps[0][gamechoice - 1] = min(levelsteps[1][gamechoice - 1], distance);
		}

		if (gamechoice < 10)
		{
			
			setbkcolor(BLACK);
			cleardevice();
			setcolor(RED);
			settextstyle(100, 0, _T("�����ֺ��μ���"));
			RECT r = { 0, 300, WIDTH, HIGH };
			drawtext(_T("��ϲ����!"), &r, DT_CENTER);
			r = { 0, 500, WIDTH, HIGH };
			drawtext(_T("���̰������������һ��!"), &r, DT_CENTER);
			FlushBatchDraw();
			_getch();
			gamechoice++;
			Mapreset();
		}
		if (gamechoice == 10)
		{
			setcolor(RED);
			settextstyle(100, 0, _T("�����ֺ��μ���"));
			RECT r = { 0, 300, WIDTH, HIGH };
			drawtext(_T("��ϲ����!"), &r, DT_CENTER);
			r = { 0, 400, WIDTH, HIGH };
			drawtext(_T("ȫ��ͨ����!"), &r, DT_CENTER);
			r = { 0, 500, WIDTH, HIGH };
			drawtext(_T("���̰���������ص��ؿ�ѡ�����"), &r, DT_CENTER);
			FlushBatchDraw();
			_getch();
			viewchoice = 1;
		}
	}
}
void Updatewithinput()
{
	int i, j;//1���ϣ�2���£�3����4����
	if ((GetAsyncKeyState(VK_CONTROL) & 0x8000))
	{
		if ((GetAsyncKeyState(0x57) & 0x8000))
		{
			Goodbye();
		}
	}
	switch (viewchoice)
	{
	case 1:
	{
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x >= WIDTH / 2 - 140 && m.x <= WIDTH / 2 + 120 && m.y >= 520 && m.y <= 620)
				{
					viewchoice = 2;
				}
			}
		}
		break;
	}
	case 2:
	{
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{

				//���·��ر�־���߷�������
				if (m.x >= 110 && m.x <= 198 && m.y >= 40 && m.y <= 158)
				{
					viewchoice = 1;
				}

				//���¹ؿ�ͼ��ѡ��ؿ�
				for (i = 1; i <= 3; i++)
				{
					for (j = 1; j <= 3; j++)
					{
						if (m.x >= i / 4.0 * WIDTH - SIZE && m.x <= i / 4.0 * WIDTH + SIZE && m.y >= 200 + (j - 1) * 140 && m.y <= 300 + (j - 1) * 140)
						{

							viewchoice = 3;
							gamechoice = 3 * (j - 1) + i;
							Mapreset();
						}
					}
				}
				if (m.x >= 1 / 4.0 * WIDTH - SIZE && m.x <= 1 / 4.0 * WIDTH + SIZE && m.y >= 200 + (j - 1) * 140 && m.y <= 300 + (j - 1) * 140)
				{
					viewchoice = 3;
					gamechoice = 10;
					Mapreset();
				}
			}
		}
		break;
	}
	case 3:
	{
		if (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x >= (WIDTH / size - 3) * size && m.x <= (WIDTH / size - 2) *size && m.y >= (HIGH / size - 3.5) * size && m.y <= (HIGH / size - 2.5) * size)
				{
					movechoice = 1;
					movetype = Move(movechoice);
				}
				if (m.x >= (WIDTH / size - 3) * size && m.x <= (WIDTH / size - 2) * size && m.y >= (HIGH / size - 2) * size && m.y <= (HIGH / size - 1) * size)
				{
					movechoice = 2;
					movetype = Move(movechoice);
				}
				if (m.x >= (WIDTH / size - 4.5) * size && m.x <= (WIDTH / size - 3.5) * size && m.y >= (HIGH / size - 2) * size && m.y <= (HIGH / size - 1) * size)
				{
					movechoice = 3;
					movetype = Move(movechoice);
				}
				if (m.x >= (WIDTH / size - 1.5) * size && m.x <= (WIDTH / size - 0.5) * size && m.y >= (HIGH / size - 2) * size && m.y <= (HIGH / size - 1) * size)
				{
					movechoice = 4;
					movetype = Move(movechoice);
				}
				if (m.x >= 850 && m.x <= 850 + 3 * SIZE && m.y >= 350 && m.y <= 350 + 3 * SIZE * 128 / 268)//����������
				{
					viewchoice = 2;
				}
				if (m.x >= 850 && m.x <= 850 + 3 * SIZE && m.y >= 450 && m.y <= 450 + 3 * SIZE * 128 / 268)//����
				{
					Mapreset();
				}
				if (m.x >= 850 && m.x <= 850 + 3 * SIZE && m.y >= 550 && m.y <= 550 + 3 * SIZE * 128 / 268)//����
				{
					if (redotimes > 0)
					{
						if (movechoice == 1)//��������
						{
							if (movetype == 1)
							{
								redotimes--;
								movetype = 0;
								position_y++;
								distance--;
							}
							if (movetype == 2)
							{
								redotimes--;
								movetype = 0;
								position_y++;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y - 2 && boxposition[0][i] == position_x)
									{
										boxposition[1][i]++;
										distance--;
									}
								}
							}
						}
						if (movechoice == 2)//��������
						{
							if (movetype == 1)
							{
								redotimes--;
								movetype = 0;
								position_y--;
								distance--;
							}
							if (movetype == 2)
							{
								redotimes--;
								movetype = 0;
								position_y--;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y + 2 && boxposition[0][i] == position_x)
									{
										boxposition[1][i]--;
										distance--;
									}
								}
							}
						}
						if (movechoice == 3)//��������
						{
							if (movetype == 1)
							{
								redotimes--;
								movetype = 0;
								position_x++;
								distance--;
							}
							if (movetype == 2)
							{
								redotimes--;
								movetype = 0;
								position_x++;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y && boxposition[0][i] == position_x - 2)
									{
										boxposition[0][i]++;
										distance--;
									}
								}
							}
						}
						if (movechoice == 4)//��������
						{
							if (movetype == 1)
							{
								movetype = 0;
								redotimes--;
								position_x--;
								distance--;
							}
							if (movetype == 2)
							{
								movetype = 0;
								redotimes--;
								position_x--;
								for (i = 0; boxposition[0][i] > 0; i++)
								{
									if (boxposition[1][i] == position_y && boxposition[0][i] == position_x + 2)
									{
										boxposition[0][i]--;
										distance--;
									}
								}
							}
						}
					}
				}
			}
		}
		if (_kbhit())
		{
			int input1;
			input1 = _getch();
			if (input1 == 56 || input1 == 119 || input1 == 72)
			{
				movechoice = 1;
				movetype = Move(movechoice);
			}
			if (input1 == 50 || input1 == 115 || input1 == 80)
			{
				movechoice = 2;
				movetype = Move(movechoice);
			}
			if (input1 == 52 || input1 == 97 || input1 == 75)
			{
				movechoice = 3;
				movetype = Move(movechoice);
			}
			if (input1 == 54 || input1 == 100 || input1 == 77)
			{
				movechoice = 4;
				movetype = Move(movechoice);
			}
		}
		break;
	}
	}
}
int Move(int movechoice)//����ֵΪmovetype������0�����޶���������1�������Լ���������2�����˺����Ӷ���
{
	int i, j, specialbox = -1;//��¼box�±�
	if (movechoice == 1)
	{
		specialbox = -1;
		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//��ǰ��ǰһ��λ����ǽ
			if (brickposition[1][i] == position_y - 1 && brickposition[0][i] == position_x)
				return 0;
		}

		//�ж����Ϸ��Ƿ������ӣ����У���¼�����±�
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[1][i] == position_y - 1 && boxposition[0][i] == position_x)
				specialbox = i;
		}
		if (specialbox == -1)//�Ϸ�λ�������ӣ��������Լ���
		{
			position_y--;
			distance++;
			return 1;
		}
		else//�Ϸ�������
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//�Ϸ�������������
				if (boxposition[1][i] == boxposition[1][specialbox] - 1 && boxposition[0][i] == boxposition[0][specialbox])
					return 0;
			}
			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//�Ϸ�������ǽ
				if (brickposition[1][j] == boxposition[1][specialbox] - 1 && brickposition[0][j] == boxposition[0][specialbox])
					return 0;
			}
			//�˺����Ӷ�����
			position_y--;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[1][i]--;
					distance++;
					return 2;
				}
			}
		}

	}
	if (movechoice == 2)
	{
		specialbox = -1;

		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//��ǰ��ǰһ��λ����ǽ
			if (brickposition[1][i] == position_y + 1 && brickposition[0][i] == position_x)
				return 0;
		}

		//�ж����·��Ƿ������ӣ����м�¼�����±�
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[1][i] == position_y + 1 && boxposition[0][i] == position_x)
				specialbox = i;
		}
		if (specialbox == -1)//�·�λ�������ӣ��������Լ���
		{
			position_y++;
			distance++;
			return 1;
		}
		else//�·�������
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//�·�������������
				if (boxposition[1][i] == boxposition[1][specialbox] + 1 && boxposition[0][i] == boxposition[0][specialbox])
					return 0;
			}


			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//�·�������ǽ
				if (brickposition[1][j] == boxposition[1][specialbox] + 1 && brickposition[0][j] == boxposition[0][specialbox])
					return 0;
			}

			//�˺����Ӷ�����
			position_y++;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[1][i]++;
					distance++;
					return 2;
				}
			}

		}
	}
	if (movechoice == 3)
	{
		specialbox = -1;

		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//��ǰ��ǰһ��λ����ǽ
			if (brickposition[0][i] == position_x - 1 && brickposition[1][i] == position_y)
				return 0;
		}

		//�ж������Ƿ������ӣ����м�¼�����±�
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[0][i] == position_x - 1 && boxposition[1][i] == position_y)
				specialbox = i;
		}
		if (specialbox == -1)//��λ�������ӣ��������Լ���
		{
			position_x--;
			distance++;
			return 1;
		}
		else//��������
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//��������������
				if (boxposition[0][i] == boxposition[0][specialbox] - 1 && boxposition[1][i] == boxposition[1][specialbox])
					return 0;
			}


			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//��������ǽ
				if (brickposition[0][j] == boxposition[0][specialbox] - 1 && brickposition[1][j] == boxposition[1][specialbox])
					return 0;
			}

			//�˺����Ӷ�����
			position_x--;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[0][i]--;
					distance++;
					return 2;
				}
			}

		}
	}
	if (movechoice == 4)
	{
		specialbox = -1;

		for (i = 0; brickposition[0][i] > 0; i++)
		{
			//��ǰ��ǰһ��λ����ǽ
			if (brickposition[0][i] == position_x + 1 && brickposition[1][i] == position_y)
				return 0;
		}

		//�ж����ҷ��Ƿ������ӣ����м�¼�����±�
		for (i = 0; boxposition[0][i] > 0; i++)
		{
			if (boxposition[0][i] == position_x + 1 && boxposition[1][i] == position_y)
				specialbox = i;
		}
		if (specialbox == -1)//�ҷ�λ�������ӣ��������Լ���
		{
			position_x++;
			distance++;
			return 1;
		}
		else//�ҷ�������
		{
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				//�ҷ�������������
				if (boxposition[0][i] == boxposition[0][specialbox] + 1 && boxposition[1][i] == boxposition[1][specialbox])
					return 0;
			}

			for (j = 0; brickposition[0][j] > 0; j++)
			{
				//�ҷ�������ǽ
				if (brickposition[0][j] == boxposition[0][specialbox] + 1 && brickposition[1][j] == boxposition[1][specialbox])
					return 0;
			}

			//�˺����Ӷ�����
			position_x++;
			for (i = 0; boxposition[0][i] > 0; i++)
			{
				if (boxposition[1][i] == position_y && boxposition[0][i] == position_x)
				{
					boxposition[0][i]++;
					distance++;
					return 2;
				}
			}

		}
	}
}
int Goodbye()
{
	int i, j = 0, k = 0;
	for (i = 0; i <= 9; i++)
	{
		if (levelsteps[0][i] == 1)
		{
			j++;
			k = k + levelsteps[1][i];
		}
	}

	SYSTEMTIME time2;
	GetLocalTime(&time2);
	int playtime;
	playtime = time2.wDay * 86400 + time2.wHour * 3600 + time2.wMinute * 60 + time2.wSecond - time1.wDay * 86400 - time1.wHour * 3600 - time1.wMinute * 60 - time1.wSecond;
	int hourtime, minutetime, secondtime;
	hourtime = playtime / 3600;
	minutetime = (playtime - hourtime * 3600) / 60;
	secondtime = playtime - hourtime * 3600 - minutetime * 60;

	setbkcolor(BLACK);
	cleardevice();
	settextstyle(96, 0, _T("�����ֺ��μ���"));

	settextcolor(RGB(255, 255, 255));
	outtextxy(200, 100, "��������Ϸʱ��Ϊ");

	char string[16] = { 0 };
	_itoa_s(hourtime, string, 10);
	settextcolor(RGB(250, 245, 240));
	outtextxy(300, 250, string);

	settextcolor(RGB(245, 235, 225));
	outtextxy(450, 250, "Сʱ");

	_itoa_s(minutetime, string, 10);
	settextcolor(RGB(240, 225, 210));
	outtextxy(650, 250, string);

	settextcolor(RGB(235, 215, 195));
	outtextxy(800, 250, "����");

	_itoa_s(secondtime, string, 10);
	outtextxy(1000, 250, string);
	settextcolor(RGB(230, 205, 180));
	outtextxy(1150, 250, "��");

	settextcolor(RGB(225, 195, 165));
	outtextxy(200, 400, "��ͨ��");

	_itoa_s(j, string, 10);
	settextcolor(RGB(220, 185, 150));
	outtextxy(500, 400, string);

	settextcolor(RGB(215, 175, 135));
	outtextxy(650, 400, "�أ�����");

	_itoa_s(k, string, 10);
	settextcolor(RGB(210, 165, 120));
	outtextxy(1000, 400, string);

	settextcolor(RGB(205, 155, 105));
	outtextxy(1200, 400, "����");

	settextcolor(RGB(200, 145, 90));
	outtextxy(200, 550, "������������ȥ��Ϣһ�°ɣ�����");

	settextcolor(RGB(195, 135, 75));
	outtextxy(200, 700, "��������˳�");
	EndBatchDraw();

	_getch();
	_getch();
	closegraph();
	exit(0);
	return 0;
}

