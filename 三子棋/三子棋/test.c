#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
void menu() //设置菜单
{
	printf("*********************\n");
	printf("*** 1. play 0.exit***\n");
	printf("*********************\n");
}
void game()//定义游戏
{
	char ret = 0;
	char board[ROW][COL] = {0};
	//初始化棋盘
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	//下棋
	while (1)
	{
		playerMove(board, ROW, COL);
		ret = Iswin(board, ROW, COL);
		if (ret != 'C') {
			break;
		}
		DisplayBoard(board, ROW, COL);
		ComputerMove(board, ROW, COL);
		ret = Iswin(board, ROW, COL);
		if (ret != 'C') {
			break;
		}
		DisplayBoard(board, ROW, COL);
	}
	if (ret == '*') {
		printf("玩家赢\n");
	}
	else if (ret == '#') {
		printf("电脑赢\n");
	}
	else {
		printf("平局\n");
	}
}
int main() {
	srand((unsigned int)time(NULL));
	int put = 0;
	do {
		menu();
		printf("选择：：>");
		scanf("%d", &put);
		switch (put) {
		case 1:
		{
			game();
				break;
		}
			
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误\n");
			break;

		}
	} while (put !=0);
	return 0;
}