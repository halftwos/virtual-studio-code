#include <graphics.h>//����ͼ�ο�ͷ�ļ�
#include <conio.h>//�����������ͷ�ļ�
#include<mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#include <windows.h>
#pragma comment(lib,"winmm.lib")//���ؾ�̬��

//ȫ�ֱ���
int num = 1;
int q;
int arr[30][30];
//����bgm
void bgm()
{
	mciSendString("open ./music.MP3", NULL, 0, NULL);//��ʼ��������

	mciSendString("play ./music.MP3 ", NULL, 0, NULL);//ѭ������
}
//�������̱���
void loadResource()
{
	IMAGE img;//����img����
	loadimage(&img, _T("starfields.png"));//��ͼƬ���ص�img
	putimage(0, 0, &img);//��ͼƬ��������ȥ������1��2ΪͼƬ�ӽ�����ĸ�λ�ÿ�ʼ�������ͼƬ
}
//���̻���
void draw()
{
	for (int x = 30; x < 960; x += 60)//ѭ��������
	{
		line(x, 30, x, 930);//���ߺ�����ǰ��������Ϊ��ʼ��x,y,����������Ϊ�յ�x,y
	}
	for (int y = 30; y < 960; y += 60)//ѭ��������
	{
		line(30, y, 930, y);
	}
	setfillcolor(BLACK);//����Բ����ɫ
	fillcircle(30 + 3 * 60, 30 + 3 * 60, 3); //ǰ��������ΪԲ��Բ�����꣬����������ΪԲ�İ뾶
	fillcircle(30 + 3 * 60, 30 + 11 * 60, 3);
	fillcircle(30 + 11 * 60, 30 + 3 * 60, 3);
	fillcircle(30 + 7 * 60, 30 + 7 * 60, 3);
	fillcircle(30 + 11 * 60, 30 + 11 * 60, 3);

}
//��ʼ����ά����
void initboard()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			arr[i][j] = 0;//ѭ����ʼ����ά����
		}
	}
}
//����Ƿ������
int full(int x, int y)
{
	if (arr[x][y] != 0)//���������0����ʾ�¹�����return 0;
		return 0;
	else//�������0����ʾû�¹����ˣ����������Ӧλ�÷�num,return 1;
		arr[x][y] = num;
	return 1;
}
//���ڰ���
void mouse(int m, int n)
{
	if (num == -1)
	{
		setfillcolor(WHITE);// ���ð���
	}
	else if (num == 1)
	{
		setfillcolor(BLACK);//���ú���
	}
	int x;
	int y;
	x = m / 60;//��ά��������꣬m�������꣬
	y = n / 60;//��ά����������n��������꣬
	if (full(x, y) == 0)//����0��ʾ�¹����ˣ�ֱ��return������mouse,���=1��������������ж���䣬��ʼ����
		return;

	int lineSpacing = 60;
	int chessRadius = 30;

	fillcircle(m - m % lineSpacing + chessRadius,
		n - n % lineSpacing + chessRadius,
		chessRadius);
	num *= -1;//�ڰ��彻��
}
//������
void pickmouse() {
	MOUSEMSG msg;//���������Ϣ
	if (MouseHit())//����������Ϣ
	{
		msg = GetMouseMsg(); //��ȡ�����Ϣ
		if (msg.uMsg == WM_LBUTTONDOWN) //������������
		{
			mouse(msg.x, msg.y);//�������������������
		}
	}
}

//�ж��Ƿ���������
int check_five(int x, int y)
{

	if (arr[x][y] == arr[x - 1][y] && arr[x][y] == arr[x - 2][y] && arr[x][y] == arr[x + 1][y] && arr[x][y] == arr[x + 2][y])
		return 1;
	if (arr[x][y] == arr[x][y - 1] && arr[x][y] == arr[x][y - 2] && arr[x][y] == arr[x][y + 1] && arr[x][y] == arr[x][y + 2])
		return 1;
	if (arr[x][y] == arr[x - 1][y - 1] && arr[x][y] == arr[x - 2][y - 2] && arr[x][y] == arr[x + 1][y + 1] && arr[x][y] == arr[x + 2][y + 2])
		return 1;
	if (arr[x][y] == arr[x - 1][y + 1] && arr[x][y] == arr[x + 2][y - 2] && arr[x][y] == arr[x + 1][y - 1] && arr[x][y] == arr[x - 2][y + 2])
		return 1;


	return 0;
}
//�ж��Ƿ����ʤ�����
int check_over()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (arr[i][j] == 0)
				continue;
			if (check_five(i, j) == 1)
			{
				q = arr[i][j];
				return 1;
			}




		}


	}

}
void change()//��Ϣ���Ӻ���,��ʾ˭Ӯ��
{

	HWND hnd = GetHWnd();  //��ȡ���ھ�����൱�ڴ��ڵ�ָ�룩
	SetWindowText(hnd, "������"); //���ô��ڱ���
	int isok;
	if (q == 1)//q��ȡ����Ӯ�Ҷ�Ӧ��ά�������Ϣ������Ϊ1											//
		isok = MessageBox(NULL, "����ʤ", "��ʾ", MB_OKCANCEL); //������Ϣ����,��ʾ�û�����
	else if (q == -1)
		isok = MessageBox(NULL, "����ʤ", "��ʾ", MB_OKCANCEL);



}

int main()
{
	bgm();
	initgraph(960, 960);//������СΪ480*480��ͼ���
	loadResource();
	draw();
	settextstyle(80, 40, "����");
	setbkmode(TRANSPARENT);
	while (1)
	{
		BeginBatchDraw();//�������ƺ����������������.
		draw();
		EndBatchDraw();//������������



		while (1)
		{
			pickmouse();
			if (check_over() == 1)
			{
				outtextxy(360, 360, "��Ϸ����");//�������,����һ������Ϊ�������Ͻ����꣬������Ϊ��������
				change();//��Ϣ���Ӻ���,��ʾ˭Ӯ��
				system("pause");//�˳�����ͷ�ļ�windows.h

			}




		}




	}



	_getch();
	return 0;
}