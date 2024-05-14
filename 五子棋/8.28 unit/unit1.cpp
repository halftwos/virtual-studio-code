#include <graphics.h>//包含图形库头文件
#include <conio.h>//控制输入输出头文件
#include<mmsystem.h>//包含多媒体设备接口头文件
#include <windows.h>
#pragma comment(lib,"winmm.lib")//加载静态库

//全局变量
int num = 1;
int q;
int arr[30][30];
//加入bgm
void bgm()
{
	mciSendString("open ./music.MP3", NULL, 0, NULL);//开始播放音乐

	mciSendString("play ./music.MP3 ", NULL, 0, NULL);//循环播放
}
//制作棋盘背景
void loadResource()
{
	IMAGE img;//创建img对象
	loadimage(&img, _T("starfields.png"));//将图片加载到img
	putimage(0, 0, &img);//贴图片到界面上去（参数1，2为图片从界面的哪个位置开始贴）输出图片
}
//棋盘绘制
void draw()
{
	for (int x = 30; x < 960; x += 60)//循环画竖线
	{
		line(x, 30, x, 930);//画线函数，前两个参数为起始点x,y,后两个参数为终点x,y
	}
	for (int y = 30; y < 960; y += 60)//循环画横线
	{
		line(30, y, 930, y);
	}
	setfillcolor(BLACK);//设置圆的颜色
	fillcircle(30 + 3 * 60, 30 + 3 * 60, 3); //前两个参数为圆的圆心坐标，第三个参数为圆的半径
	fillcircle(30 + 3 * 60, 30 + 11 * 60, 3);
	fillcircle(30 + 11 * 60, 30 + 3 * 60, 3);
	fillcircle(30 + 7 * 60, 30 + 7 * 60, 3);
	fillcircle(30 + 11 * 60, 30 + 11 * 60, 3);

}
//初始化二维数组
void initboard()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			arr[i][j] = 0;//循环初始化二维数组
		}
	}
}
//检查是否可落子
int full(int x, int y)
{
	if (arr[x][y] != 0)//如果不等于0，表示下过棋了return 0;
		return 0;
	else//如果等于0，表示没下过棋了，将该数组对应位置放num,return 1;
		arr[x][y] = num;
	return 1;
}
//画黑白棋
void mouse(int m, int n)
{
	if (num == -1)
	{
		setfillcolor(WHITE);// 设置白棋
	}
	else if (num == 1)
	{
		setfillcolor(BLACK);//设置黑棋
	}
	int x;
	int y;
	x = m / 60;//二维数组横坐标，m鼠标横坐标，
	y = n / 60;//二维数组纵坐标n鼠标纵坐标，
	if (full(x, y) == 0)//等于0表示下过棋了，直接return；跳出mouse,如果=1，跳过这个条件判断语句，开始下棋
		return;

	int lineSpacing = 60;
	int chessRadius = 30;

	fillcircle(m - m % lineSpacing + chessRadius,
		n - n % lineSpacing + chessRadius,
		chessRadius);
	num *= -1;//黑白棋交替
}
//点击鼠标
void pickmouse() {
	MOUSEMSG msg;//定义鼠标信息
	if (MouseHit())//如果鼠标有信息
	{
		msg = GetMouseMsg(); //获取鼠标信息
		if (msg.uMsg == WM_LBUTTONDOWN) //如果点击鼠标左键
		{
			mouse(msg.x, msg.y);//棋子下在鼠标所点坐标
		}
	}
}

//判断是否五子连线
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
//判断是否产生胜负结果
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
void change()//消息盒子函数,提示谁赢了
{

	HWND hnd = GetHWnd();  //获取窗口句柄（相当于窗口的指针）
	SetWindowText(hnd, "五子棋"); //设置窗口标题
	int isok;
	if (q == 1)//q获取的是赢家对应二维数组的消息，黑子为1											//
		isok = MessageBox(NULL, "黑子胜", "提示", MB_OKCANCEL); //弹出消息盒子,提示用户操作
	else if (q == -1)
		isok = MessageBox(NULL, "白子胜", "提示", MB_OKCANCEL);



}

int main()
{
	bgm();
	initgraph(960, 960);//创建大小为480*480的图像框
	loadResource();
	draw();
	settextstyle(80, 40, "宋体");
	setbkmode(TRANSPARENT);
	while (1)
	{
		BeginBatchDraw();//批量绘制函数，解决闪屏问题.
		draw();
		EndBatchDraw();//结束批量绘制



		while (1)
		{
			pickmouse();
			if (check_over() == 1)
			{
				outtextxy(360, 360, "游戏结束");//输出文字,参数一参数二为文字左上角坐标，参数三为文字内容
				change();//消息盒子函数,提示谁赢了
				system("pause");//退出程序，头文件windows.h

			}




		}




	}



	_getch();
	return 0;
}